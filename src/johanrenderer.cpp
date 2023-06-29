#include "johanrenderer.h"

#include <QPainter>
#include <QPixmap>
#include <chrono>

JohanRenderer::JohanRenderer(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_camera(45.0f, 0.1f, 100.0f)
{
    m_image = new QImage(width(), height(), QImage::Format_RGBA8888);
    connect(this, &JohanRenderer::widthChanged, this, &JohanRenderer::handleSizeChanged);
    connect(this, &JohanRenderer::heightChanged, this, &JohanRenderer::handleSizeChanged);
}

void JohanRenderer::render() {
    auto start = std::chrono::high_resolution_clock::now();

    // RENDERING
    m_camera.OnUpdate(1.0);
    m_camera.OnResize(width(), height());
    m_renderer.onResize(width(), height());
    m_renderer.render(m_camera);

    auto* data = m_renderer.imageData();
    for (int y = 0; y < m_image->height(); ++y) {
        for (int x = 0; x < m_image->width(); ++x) {
            uint32_t color = data[y * m_image->width() + x];
            auto r = (color >> 0) & 0xFF; // flipped
            auto g = (color >> 8) & 0xFF;
            auto b = (color >> 16) & 0xFF; // flipped :)
            m_image->setPixelColor(x, m_image->height() - y - 1, QColor(r, g, b));
        }
    }
    // RENDERING

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    m_renderTime = duration;
    emit renderTimeChanged();
    update();
}

void JohanRenderer::paint(QPainter *painter) {
    painter->drawImage(0, 0, *m_image);
    
    if (m_autoRender)
        render();
}

void JohanRenderer::handleSizeChanged() {
    delete m_image;
    m_image = new QImage(width(), height(), QImage::Format_RGBA8888);
}

double JohanRenderer::renderTime() const {
    return m_renderTime;
}

bool JohanRenderer::autoRender() const {
    return m_autoRender;
}

void JohanRenderer::setAutoRender(bool autoRender) {
    if (m_autoRender == autoRender)
        return;

    m_autoRender = autoRender;
    emit autoRenderChanged();
}