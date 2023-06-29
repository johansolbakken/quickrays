#include "renderer.h"

#include <glm/glm.hpp>

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
}

void Renderer::onResize(uint32_t width, uint32_t height)
{
    if (m_width == width && m_height == height)
        return;
    m_width = width;
    m_height = height;
    delete[] m_imageData;
    m_imageData = new uint32_t[width * height];
}

void Renderer::render(const Camera &camera)
{
    auto rayOrigin = camera.GetPosition();
    Ray ray;
    ray.origin = rayOrigin;

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            auto rayDirection = camera.GetRayDirections()[x + y * m_width];
            ray.direction = rayDirection;

            auto color = traceRay(ray);
            color = glm::clamp(color, glm::vec4(0.0), glm::vec4(1.0));
            m_imageData[y * m_width + x] = Utils::conertToRGBA(color);
        }
    }
}

glm::vec4 Renderer::traceRay(const Ray& ray)
{
    float radius = 0.5;

    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0 * glm::dot(ray.direction, ray.origin);
    float c = glm::dot(ray.origin, ray.origin) - radius * radius;

    float discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return glm::vec4(0.0);

    float t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0.0)
        return glm::vec4(0.0);

    glm::vec3 hitPoint = ray.origin + ray.direction * t;
    glm::vec3 normal = glm::normalize(hitPoint);
    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, -1));
    float lightIntensity = glm::dot(normal, -lightDirection);
    if (lightIntensity < 0.0)
        lightIntensity = 0.0;

    auto sphereColor = glm::vec3(1, 0, 1);
    sphereColor *= lightIntensity;
    return glm::vec4(sphereColor, 1.0);
}