#include "renderer.h"

#include <glm/glm.hpp>
#include <random>
#include <algorithm>
#include <QThread>
#include <execution>

namespace Utils
{
    static uint32_t conertToRGBA(const glm::vec4 &color)
    {
        auto r = (uint32_t)(color.r * 255.0f);
        auto g = (uint32_t)(color.g * 255.0f);
        auto b = (uint32_t)(color.b * 255.0f);
        auto a = (uint32_t)(color.a * 255.0f);

        return (a << 24) | (b << 16) | (g << 8) | r;
    }

    static auto generator = std::mt19937(std::random_device()());

    static float randomFloat(float min = 0.0f, float max = 1.0f)
    {
        static auto distribution = std::uniform_real_distribution<float>(min, max);
        return distribution(generator);
    }

    static glm::vec3 randomVec3(float min = 0.0f, float max = 1.0f)
    {
        return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
    }
}

void Renderer::onResize(uint32_t width, uint32_t height)
{
    if (m_width == width && m_height == height)
        return;
    m_width = width;
    m_height = height;
    delete[] m_imageData;
    m_imageData = new uint32_t[width * height];
    delete[] m_accumulationData;
    m_accumulationData = new glm::vec4[width * height];

    m_imageHorizontalIter.resize(width);
    m_imageVerticalIter.resize(height);
    for (int i = 0; i < width; ++i)
        m_imageHorizontalIter[i] = i;
    for (int i = 0; i < height; ++i)
        m_imageVerticalIter[i] = i;
}

void Renderer::render(const Scene &scene, const Camera &camera)
{
    if (m_width == 0 || m_height == 0)
        return;

    m_activeScene = &scene;
    m_activeCamera = &camera;

    if (m_frameIndex == 1)
        memset(m_accumulationData, 0, m_width * m_height * sizeof(glm::vec4));

    if (m_settings.multiThreaded)
    {
        std::vector<std::thread> threads(m_height);
        for (int y = 0; y < m_height; y++)
        {
            threads[y] = std::thread([this, y]()
                                     {
                    for (int x = 0; x < m_width; x++) {
                    auto color = perPixel(x, y);
                    m_accumulationData[y * m_width + x] += color;
                    glm::vec4 accumulatedColor = m_accumulationData[y * m_width + x] / (float)m_frameIndex;
                    accumulatedColor = glm::clamp(accumulatedColor, glm::vec4(0.0), glm::vec4(1.0));
                    m_imageData[y * m_width + x] = Utils::conertToRGBA(accumulatedColor);
                    } });
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
    }
    else
    {
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                auto color = perPixel(x, y);
                m_accumulationData[y * m_width + x] += color;
                glm::vec4 accumulatedColor = m_accumulationData[y * m_width + x] / (float)m_frameIndex;
                accumulatedColor = glm::clamp(accumulatedColor, glm::vec4(0.0), glm::vec4(1.0));
                m_imageData[y * m_width + x] = Utils::conertToRGBA(accumulatedColor);
            }
        }
    }

    if (m_settings.accumulate)
        m_frameIndex++;
    else
        m_frameIndex = 1;
}

glm::vec4 Renderer::perPixel(uint32_t x, uint32_t y)
{
    Ray ray;
    ray.origin = m_activeCamera->GetPosition();
    ray.direction = m_activeCamera->GetRayDirections()[x + y * m_width];

    glm::vec3 color(0.0);
    float multiplier = 1.0;

    for (int i = 0; i < m_settings.bounces; ++i)
    {
        auto payload = traceRay(ray);
        if (payload.objectIndex < 0)
        {
            glm::vec3 skyColor(0.6, 0.7, 0.9);
            color += skyColor * multiplier;
            break;
        }

        glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, -1));
        float lightIntensity = glm::dot(payload.worldNormal, -lightDirection);
        if (lightIntensity < 0.0)
            lightIntensity = 0.0;

        auto &closestSphere = m_activeScene->spheres[payload.objectIndex];
        auto &material = m_activeScene->materials[closestSphere.materialIndex];
        auto sphereColor = material.albedo;
        sphereColor *= lightIntensity;
        color += sphereColor * multiplier;

        multiplier *= 0.5;

        ray.origin = payload.worldPosition + payload.worldNormal * 0.001f;
        ray.direction = glm::reflect(ray.direction, payload.worldNormal + Utils::randomVec3(-0.5, 0.5) * material.roughness);
    }

    return glm::vec4(color, 1.0);
}

Renderer::HitPayload Renderer::traceRay(const Ray &ray)
{
    int closestSphere = -1;
    float hitDistance = std::numeric_limits<float>::max();

    for (uint32_t i = 0; i < m_activeScene->spheres.size(); ++i)
    {
        auto &sphere = m_activeScene->spheres[i];
        glm::vec3 origin = ray.origin - sphere.position;

        float a = glm::dot(ray.direction, ray.direction);
        float b = 2.0 * glm::dot(ray.direction, origin);
        float c = glm::dot(origin, origin) - sphere.radius * sphere.radius;

        float discriminant = b * b - 4.0 * a * c;
        if (discriminant < 0.0)
            continue;

        float closestT = (-b - sqrt(discriminant)) / (2.0 * a);
        if (closestT > 0 && closestT < hitDistance)
        {
            hitDistance = closestT;
            closestSphere = i;
        }
    }

    if (closestSphere < 0)
        return miss(ray);

    return closestHit(ray, hitDistance, closestSphere);
}

Renderer::HitPayload Renderer::closestHit(const Ray &ray, float hitDistance, int objectIndex)
{
    HitPayload payload;
    payload.hitDistance = hitDistance;
    payload.objectIndex = objectIndex;

    auto &closestSphere = m_activeScene->spheres[objectIndex];
    auto origin = ray.origin - closestSphere.position; // move origin to sphere center
    payload.worldPosition = origin + ray.direction * hitDistance;
    payload.worldNormal = glm::normalize(payload.worldPosition);
    payload.worldPosition += closestSphere.position; // move back to world space

    return payload;
}

Renderer::HitPayload Renderer::miss(const Ray &ray)
{
    HitPayload payload;
    payload.hitDistance = std::numeric_limits<float>::max();
    payload.objectIndex = -1;

    return payload;
}
