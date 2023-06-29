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

void Renderer::render()
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            glm::vec2 coord = {(float)x / (float)m_width, (float)y / (float)m_height};
            coord = coord * 2.0f - 1.0f;

            auto color = perPixel(coord);
            color = glm::clamp(color, glm::vec4(0.0), glm::vec4(1.0));
            m_imageData[y * m_width + x] = Utils::conertToRGBA(color);
        }
    }
}

glm::vec4 Renderer::perPixel(glm::vec2 coord)
{
    glm::vec3 rayOrigin = {0, 0, 2.0};
    glm::vec3 rayDirection = {coord.x, coord.y, -1.0};
    float radius = 0.5;

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0 * glm::dot(rayDirection, rayOrigin);
    float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

    float discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0)
        return glm::vec4(0.0);

    float t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0.0)
        return glm::vec4(0.0);

    glm::vec3 hitPoint = rayOrigin + rayDirection * t;
    glm::vec3 normal = glm::normalize(hitPoint);
    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, -1));
    float lightIntensity = glm::dot(normal, -lightDirection);
    if (lightIntensity < 0.0)
        lightIntensity = 0.0;

    auto sphereColor = glm::vec3(1, 0, 1);
    sphereColor *= lightIntensity;
    return glm::vec4(sphereColor, 1.0);
}