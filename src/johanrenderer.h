#ifndef JOHANRENDERER_H
#define JOHANRENDERER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>

#include "renderer.h"

class JohanRenderer : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double renderTime READ renderTime NOTIFY renderTimeChanged)
    Q_PROPERTY(bool autoRender READ autoRender WRITE setAutoRender NOTIFY autoRenderChanged)
public:
    explicit JohanRenderer(QQuickItem *parent = nullptr);

    double renderTime() const;

    bool autoRender() const;
    void setAutoRender(bool autoRender);

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
};

#endif // JOHANRENDERER_H
