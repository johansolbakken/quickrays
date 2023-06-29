#ifndef JOHANRENDERER_H
#define JOHANRENDERER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>

class JohanRenderer : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double renderTime READ renderTime NOTIFY renderTimeChanged)
public:
    explicit JohanRenderer(QQuickItem *parent = nullptr);

    double renderTime() const;

protected:
    void paint(QPainter *painter) override;

signals:
    void renderTimeChanged();

public slots:
    void render();
    void handleSizeChanged();

private:
    QImage* m_image;
    double m_renderTime;

};

#endif // JOHANRENDERER_H
