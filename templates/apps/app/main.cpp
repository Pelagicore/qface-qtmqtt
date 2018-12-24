#include <QtGui>
#include <QtQml>


{% for module in system.modules %}
{% for interface in module.interfaces %}
#include "{{interface|lower}}client.h"
{% endfor %}
{% endfor %}

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

{% for module in system.modules %}
{% set major = module.majorVersion %}
{% set minor = module.minorVersion %}
{% for interface in module.interfaces %}
    qmlRegisterType<{{interface}}Client>("{{module}}", {{major}}, {{minor}}, "{{interface}}Client");
{% endfor %}
{% endfor %}

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}