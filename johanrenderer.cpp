#include "johanrenderer.h"

#include <QPainter>
#include <QPixmap>
#include <chrono>

JohanRenderer::JohanRenderer(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_image = new QImage(width(), height(), QImage::Format_RGBA8888);
    connect(this, &JohanRenderer::widthChanged, this, &JohanRenderer::handleSizeChanged);
    connect(this, &JohanRenderer::heightChanged, this, &JohanRenderer::handleSizeChanged);
}

void JohanRenderer::render() {
    auto start = std::chrono::high_resolution_clock::now();
    for (int y = 0; y < m_image->height(); ++y) {
        for (int x = 0; x < m_image->width(); ++x) {
            m_image->setPixelColor(x, y, QColor(255, 0, 0));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    m_renderTime = duration;
    emit renderTimeChanged();
    update();
}

void JohanRenderer::paint(QPainter *painter) {
    painter->drawImage(0, 0, *m_image);
}

void JohanRenderer::handleSizeChanged() {
    delete m_image;
    m_image = new QImage(width(), height(), QImage::Format_RGBA8888);
}

double JohanRenderer::renderTime() const {
    return m_renderTime;
}
