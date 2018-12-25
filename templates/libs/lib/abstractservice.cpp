#include <QtCore>
#include "{{module.module_name|lower}}shared.h"

{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = 'Abstract{0}Service'.format(interface) %}

#include "{{class|lower}}.h"
#include "shared.h"

{{ module|qt.open_ns }}

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
    , m_connection(new MqttClient(this))
{
    qCDebug({{interface}}ServiceCategory) << __func__;
    connect(m_connection, &MqttClient::received, this, &{{class}}::onReceived);
    m_connection->subscribe("{{module|lower}}/{{interface}}/#");
}

{{class}}::~{{class}}()
{
    qCDebug({{interface}}ServiceCategory) << __func__;
}

{% for property in interface.properties %}
void {{class}}::push{{property|upperfirst}}({{ property|qt.parameterType }})
{
    qCDebug({{interface}}ServiceCategory) << __func__;
    m_connection->publish("{{module|lower}}/{{interface}}/{{property}}", QVariantMap{ {"{{property}}", {{property}} } });
}
{% endfor %}

void {{class}}::onReceived(const QString& topic, const QVariantMap& data)
{
    qCDebug({{interface}}ServiceCategory) << __func__;
{% for property in interface.properties %}
    if(topic == "{{module|lower}}/{{interface}}/{{property}}") {
        set{{property|upperfirst}}(data.value("{{property}}").value<{{property|qt.returnType}}>());
    }
{% endfor %}
{% for operation in interface.operations %}
    if(topic == "{{module|lower}}/{{interface}}/{{operation}}") {
        {{operation}}(
            {% for parameter in operation.parameters %}
            data.value("{{parameter}}").value<{{parameter|qt.returnType}}>(){% if not loop.last%},{% endif %}

            {% endfor %}
        );
    }
{% endfor %}
}

{{ module|qt.close_ns }}

