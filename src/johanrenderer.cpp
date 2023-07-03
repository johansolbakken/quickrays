#include "johanrenderer.h"

#include <QPainter>
#include <QPixmap>
#include <chrono>

JohanRenderer::JohanRenderer(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_camera(45.0f, 0.1f, 100.0f), m_autoRender(true)
{
    m_image = new QImage(width(), height(), QImage::Format_RGBA8888);
    connect(this, &JohanRenderer::widthChanged, this, &JohanRenderer::handleSizeChanged);
    connect(this, &JohanRenderer::heightChanged, this, &JohanRenderer::handleSizeChanged);

    Material defaultMaterial;
    defaultMaterial.albedo = {0.7f, 0.7f, 0.7f};
    defaultMaterial.roughness = 1.0f;

    Material green;
    green.albedo = {31.0f / 255, 1.0f, 0.0f};

    Material blue;
    blue.albedo = {51.0 / 255.0, 77.0 / 255.0, 1.0f};
    blue.roughness = 0.1f;

    Material emissive;
    emissive.albedo = {0.8f, 0.5f, 0.2f};
    emissive.roughness = 0.0f;
    emissive.emissionPower = 2.0f;
    emissive.emissionColor = {0.8f, 0.5f, 0.2f};

    m_scene.materials = {green, blue, emissive};

    m_scene.spheres.push_back(Sphere{glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0});
    m_scene.spheres.push_back(Sphere{glm::vec3(0.0f, -101.0f, 0.0f), 100.0f, 1});
    m_scene.spheres.push_back(Sphere{glm::vec3(2.0f, 0.0, 0.0), 1.0, 2});
}

void JohanRenderer::render()
{
    auto start = std::chrono::high_resolution_clock::now();

    // RENDERING
    if (m_camera.OnUpdate(1.0))
        m_renderer.resetFrameIndex();
    m_camera.OnResize(width(), height());
    m_renderer.onResize(width(), height());
    m_renderer.render(m_scene, m_camera);

    auto *data = m_renderer.imageData();
    for (int y = 0; y < m_image->height(); ++y)
    {
        for (int x = 0; x < m_image->width(); ++x)
        {
            uint32_t color = data[y * m_image->width() + x];
            auto r = (color >> 0) & 0xFF; // flipped
            auto g = (color >> 8) & 0xFF;
            auto b = (color >> 16) & 0xFF; // flipped :)
            m_image->setPixelColor(x, m_image->height() - y - 1, QColor(r, g, b));
        }
    }
    // RENDERING

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    m_renderTime = duration;
    emit renderTimeChanged();
    update();
}

void JohanRenderer::paint(QPainter *painter)
{
    painter->drawImage(0, 0, *m_image);

    if (m_autoRender)
        render();
}

void JohanRenderer::handleSizeChanged()
{
    delete m_image;
    m_image = new QImage(width(), height(), QImage::Format_RGBA8888);
}

double JohanRenderer::renderTime() const
{
    return m_renderTime;
}

bool JohanRenderer::autoRender() const
{
    return m_autoRender;
}

void JohanRenderer::setAutoRender(bool autoRender)
{
    if (m_autoRender == autoRender)
        return;

    m_autoRender = autoRender;
    emit autoRenderChanged();
}

uint32_t JohanRenderer::bounces() const
{
    return m_renderer.settings().bounces;
}

void JohanRenderer::setBounces(uint32_t bounces)
{
    if (m_renderer.settings().bounces == bounces)
        return;

    m_renderer.settings().bounces = bounces;
    emit bouncesChanged();
}

bool JohanRenderer::accumulate() const
{
    return m_renderer.settings().accumulate;
}

void JohanRenderer::setAccumulate(bool accumulate)
{
    if (m_renderer.settings().accumulate == accumulate)
        return;

    m_renderer.settings().accumulate = accumulate;
    emit accumulateChanged();
}

bool JohanRenderer::multiThreaded() const
{
    return false;
}

void JohanRenderer::setMultiThreaded(bool multiThreaded)
{
    if (m_renderer.settings().multiThreaded == multiThreaded)
        return;

    m_renderer.settings().multiThreaded = multiThreaded;
    emit multiThreadedChanged();
}