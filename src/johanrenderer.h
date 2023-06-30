#ifndef JOHANRENDERER_H
#define JOHANRENDERER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>

#include "renderer.h"
#include "camera.h"
#include "scene.h"

class JohanRenderer : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double renderTime READ renderTime NOTIFY renderTimeChanged)
    Q_PROPERTY(bool autoRender READ autoRender WRITE setAutoRender NOTIFY autoRenderChanged)
    Q_PROPERTY(Camera* camera READ camera CONSTANT)
    Q_PROPERTY(uint32_t bounces READ bounces WRITE setBounces NOTIFY bouncesChanged)
    Q_PROPERTY(bool accumulate READ accumulate WRITE setAccumulate NOTIFY accumulateChanged)
public:
    explicit JohanRenderer(QQuickItem *parent = nullptr);

    double renderTime() const;

    bool autoRender() const;
    void setAutoRender(bool autoRender);

    uint32_t bounces() const;
    void setBounces(uint32_t bounces);

    bool accumulate() const;
    void setAccumulate(bool accumulate);

    Camera* camera() { return &m_camera; }

protected:
    void paint(QPainter *painter) override;

signals:
    void renderTimeChanged();
    void autoRenderChanged();
    void bouncesChanged();
    void accumulateChanged();

public slots:
    void render();
    void handleSizeChanged();

private:
    QImage* m_image;
    double m_renderTime;
    bool m_autoRender;

    Renderer m_renderer;
    Camera m_camera;
    Scene m_scene;
};

#endif // JOHANRENDERER_H
