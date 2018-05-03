{# Copyright (c) Pelagicore AB 2018 #}
{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = '{0}Client'.format(interface) %}

#pragma once

#include <QtCore>
#include <QtQml>

class MqttClient;

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
    {{ cpp.operation_decl(operation) }}
{% endfor %}
protected Q_SLOTS:
    void onReceived(const QString& topic, const QVariantMap& data);
public:
{% for property in interface.properties %}
    Q_INVOKABLE void push{{property|upperfirst}}({{ property|parameterType }}){{ending}};
    {{ cpp.property_setter_decl(property) }}
    {{ cpp.property_getter_decl(property) }}
{% endfor %}
Q_SIGNALS:
{% for property in interface.properties %}
    {{ cpp.signal_decl(property, postfix="Changed") }}
{% endfor %}
{% for signal in interface.signals %}
    {{ cpp.signal_decl(signal) }}
{% endfor %}
private:
    MqttClient *m_connection;
{% for property in interface.properties %}
    {{ cpp.property_member_decl(property) }}
{% endfor %}
};
