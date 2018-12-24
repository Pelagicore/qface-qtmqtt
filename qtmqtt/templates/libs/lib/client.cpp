{# Copyright (c) Pelagicore AB 2016 #}
{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = '{0}Client'.format(interface) %}

#include "{{class|lower}}.h"
#include "mqttclient.h"
#include "{{module.module_name|lower}}shared.h"

{{interface.comment}}
{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
    , m_connection(new MqttClient(this))
{% for property in interface.properties %}
    , m_{{property}}({{property|defaultValue}})
{% endfor %}
{
    connect(m_connection, &MqttClient::received, this, &{{class}}::onReceived);
    m_connection->subscribe("{{module|lower}}/{{interface}}/#");
}

{{class}}::~{{class}}()
{
}

{% for property in interface.properties %}

void {{class}}::push{{property|upperfirst}}({{ property|parameterType }})
{
    m_connection->publish("{{module|lower}}/{{interface}}/{{property}}", QVariantMap{ {"{{property}}", {{property}} } });
}

{{ cpp.property_setter_impl(class, property) }}

{{ cpp.property_getter_impl(class, property) }}
{% endfor %}


{%- for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
    m_connection->publish("{{module|lower}}/{{interface}}/{{operation}}");
}

{% endfor %}

void {{class}}::onReceived(const QString& topic, const QVariantMap& data)
{
{% for property in interface.properties %}
    if(topic == "{{module|lower}}/{{interface}}/{{property}}") {
        set{{property|upperfirst}}(data.value("{{property}}").value<{{property|returnType}}>());
    }
{% endfor %}
}

