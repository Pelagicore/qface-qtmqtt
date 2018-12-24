#include <QtCore>
#include "{{module.module_name|lower}}shared.h"

{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = 'Abstract{0}Service'.format(interface) %}

#include "{{class|lower}}.h"

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
    , m_connection(new MqttClient(this))
{
    qCDebug({{interface|lower}}Service) << __func__;
    connect(m_connection, &MqttClient::received, this, &{{class}}::onReceived);
    m_connection->subscribe("{{module|lower}}/{{interface}}/#");
}

{{class}}::~{{class}}()
{
    qCDebug({{interface|lower}}Service) << __func__;
}

{% for property in interface.properties %}
void {{class}}::push{{property|upperfirst}}({{ property|parameterType }})
{
    qCDebug({{interface|lower}}Service) << __func__;
    m_connection->publish("{{module|lower}}/{{interface}}/{{property}}", QVariantMap{ {"{{property}}", {{property}} } });
}
{% endfor %}

void {{class}}::onReceived(const QString& topic, const QVariantMap& data)
{
    qCDebug({{interface|lower}}Service) << __func__;
{% for property in interface.properties %}
    if(topic == "{{module|lower}}/{{interface}}/{{property}}") {
        set{{property|upperfirst}}(data.value("{{property}}").value<{{property|returnType}}>());
    }
{% endfor %}
{% for operation in interface.operations %}
    if(topic == "{{module|lower}}/{{interface}}/{{operation}}") {
        {{operation}}(
            {% for parameter in operation.parameters %}
            data.value("{{parameter}}").value<{{parameter|returnType}}>(){% if not loop.last%},{% endif %}

            {% endfor %}
        );
    }
{% endfor %}
}

