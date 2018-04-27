#include <QtGui>
#include <QtQml>

#include "mqttclient.h"
#include "counterclient.h"
#include "counterservice.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<MqttClient>("org.example", 1, 0, "MqttClient");
    qmlRegisterType<CounterClient>("org.example", 1, 0, "CounterClient");
    qmlRegisterType<CounterService>("org.example", 1, 0, "CounterService");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
