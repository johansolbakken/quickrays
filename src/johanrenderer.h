#ifndef JOHANRENDERER_H
#define JOHANRENDERER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>

#include "renderer.h"
#include "camera.h"

class JohanRenderer : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double renderTime READ renderTime NOTIFY renderTimeChanged)
    Q_PROPERTY(bool autoRender READ autoRender WRITE setAutoRender NOTIFY autoRenderChanged)
    Q_PROPERTY(Camera* camera READ camera CONSTANT)
public:
    explicit JohanRenderer(QQuickItem *parent = nullptr);

    double renderTime() const;

    bool autoRender() const;
    void setAutoRender(bool autoRender);

    Camera* camera() { return &m_camera; }

protected:
    void paint(QPainter *painter) override;

signals:
    void renderTimeChanged();
    void autoRenderChanged();

public slots:
    void render();
    void handleSizeChanged();

private:
    QImage* m_image;
    double m_renderTime;
    bool m_autoRender;

    Renderer m_renderer;
    Camera m_camera;
};

#endif // JOHANRENDERER_H
