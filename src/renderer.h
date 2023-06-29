#pragma once

#include <cstdint>
#include <glm/glm.hpp>

class Renderer 
{
public:
    void onResize(uint32_t width, uint32_t height);
    void render();

    glm::vec4 perPixel(glm::vec2 coord);

    uint32_t* imageData() const { return m_imageData; }

private:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint32_t* m_imageData = nullptr;
};