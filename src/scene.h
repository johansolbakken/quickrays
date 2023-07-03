#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Material
{
    glm::vec3 albedo{1.0f};
    float roughness = 1.0f;
    float metallic = 0.0f;
    float emissionPower = 0.0f;
    glm::vec3 emissionColor{0.0f};

    glm::vec3 getEmission() const {
        return emissionPower * emissionColor;
    }
};

struct Sphere
{
    glm::vec3 position{0.0f};
    float radius;
    uint32_t materialIndex;
};

struct Scene
{
    std::vector<Sphere> spheres;
    std::vector<Material> materials;
};
