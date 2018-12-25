{# Copyright (c) Pelagicore AB 2018 #}
{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = 'Abstract{0}Service'.format(interface) %}

#pragma once

#include <QtCore>

#include "mqttclient.h"

{{ module|qt.open_ns }}

class {{class}} : public QObject
{
    Q_OBJECT
{% for property in interface.properties %}
    {{ cpp.property_decl(property) }}
{% endfor %}
public:
    explicit {{class}}(QObject *parent = nullptr);
    ~{{class}}();
public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|qt.returnType}} {{operation}}({{operation|qt.parameters}}) = 0;
{% endfor %}
protected Q_SLOTS:
    void onReceived(const QString& topic, const QVariantMap& data);
public:
{% for property in interface.properties %}
    Q_INVOKABLE void push{{property|upperfirst}}({{ property|qt.parameterType }}){{ending}};
    virtual void set{{property|upperfirst}}({{ property|qt.parameterType }}) = 0;
    virtual {{property|qt.returnType}} {{property}}() const = 0;
{% endfor %}
Q_SIGNALS:
{% for property in interface.properties %}
    {{ cpp.signal_decl(property, postfix="Changed") }}
{% endfor %}
{% for signal in interface.signals %}
    signal_decl(signal)
{% endfor %}
private:
    MqttClient *m_connection;
};

{{ module|qt.close_ns }}
