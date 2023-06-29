#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "johanrenderer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<JohanRenderer>("QuickRays3", 1, 0, "JohanRenderer");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QuickRays3", "Main");

    return app.exec();
}
