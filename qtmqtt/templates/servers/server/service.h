{# Copyright (c) Pelagicore AB 2018 #}
{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = '{0}Service'.format(interface) %}

#include <QtCore>

#include "abstract{{class|lower}}.h"


class {{class}} : public Abstract{{class}}
{
    Q_OBJECT
{% for property in interface.properties %}
    {{ cpp.property_decl(property) }}
{% endfor %}
public:
    explicit {{class}}(QObject *parent = nullptr);
public:
{% for property in interface.properties %}
    {{ cpp.property_setter_decl(property) }}
    {{ cpp.property_getter_decl(property) }}
{% endfor %}
{% for operation in interface.operations %}
    Q_INVOKABLE {{ cpp.operation_decl(operation) }}
{% endfor %}
private:
{% for property in interface.properties %}
    {{ cpp.property_member_decl(property) }}
{% endfor %}
};
