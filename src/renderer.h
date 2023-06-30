#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "camera.h"
#include "scene.h"
#include "ray.h"

class Renderer
{
public:
    struct Settings {
        bool accumulate = true;
        uint32_t bounces = 2;
        bool multiThreaded = false;
    };

public:
    void onResize(uint32_t width, uint32_t height);
    void render(const Scene &scene, const Camera &camera);

    uint32_t *imageData() const { return m_imageData; }

    void resetFrameIndex() { m_frameIndex = 1; }
    Settings& settings() { return m_settings; }
    const Settings& settings() const { return m_settings; }

private:
    struct HitPayload
    {
        float hitDistance;
        glm::vec3 worldPosition;
        glm::vec3 worldNormal;
        int objectIndex;
    };

    glm::vec4 perPixel(uint32_t x, uint32_t y); // RayGen
    HitPayload traceRay(const Ray &ray);
    HitPayload closestHit(const Ray &ray, float hitDistance, int objectIndex);
    HitPayload miss(const Ray &ray);

private:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint32_t *m_imageData = nullptr;
    glm::vec4 *m_accumulationData = nullptr;
    uint32_t m_frameIndex = 1;
    Settings m_settings;

    std::vector<uint32_t> m_imageHorizontalIter, m_imageVerticalIter;

    const Scene *m_activeScene = nullptr;
    const Camera *m_activeCamera = nullptr;
};