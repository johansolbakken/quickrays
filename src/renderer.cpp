#include "renderer.h"

void Renderer::onResize(uint32_t width, uint32_t height) {
    if (m_width == width && m_height == height)
        return;
    m_width = width;
    m_height = height;
    delete[] m_imageData;
    m_imageData = new uint32_t[width * height];
}

void Renderer::render() {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            uint32_t r = (x * 255) / m_width;
            uint32_t g = (y * 255) / m_height;
            uint32_t b = 0;
            m_imageData[y * m_width + x] = (255 << 24) | (r << 16) | (g << 8) | b;
        }
    }
}