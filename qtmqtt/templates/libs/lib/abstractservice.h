{# Copyright (c) Pelagicore AB 2018 #}
{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = 'Abstract{0}Service'.format(interface) %}

#pragma once

#include <QtCore>

#include "mqttclient.h"

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
    virtual {{operation|returnType}} {{operation}}({{operation|parameters}}) = 0;
{% endfor %}
protected Q_SLOTS:
    void onReceived(const QString& topic, const QVariantMap& data);
public:
{% for property in interface.properties %}
    Q_INVOKABLE void push{{property|upperfirst}}({{ property|parameterType }}){{ending}};
    virtual void set{{property|upperfirst}}({{ property|parameterType }}) = 0;
    virtual {{property|returnType}} {{property}}() const = 0;
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
