#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "barmodel.h"
#include "beatmodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<models::BarModel>("BarModel", 1, 0, "BarModel");
    qmlRegisterType<models::BeatModel>("BeatModel", 1, 0, "BeatModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
