#include <QtCore>

{% import "qface/qtcpp.j2" as cpp %}
{{ cpp.preserved() }}
{% set class = '{0}Service'.format(interface) %}

#include "{{class|lower}}.h"

{{class}}::{{class}}(QObject *parent)
    : Abstract{{class}}(parent)
{% for property in interface.properties %}
    , m_{{property}}({{property|defaultValue}})
{% endfor %}
{
}

{{class}}::~{{class}}()
{
}

{% for property in interface.properties %}
void {{class}}::set{{property|upperfirst}}({{ property|parameterType }})
{
    push{{property|upperfirst}}({{ property }});
}

{{ cpp.property_getter_impl(class, property) }}
{% endfor %}

{% for operation in interface.operations %}
    {{ cpp.operation_impl(class, operation) }}
{% endfor %}

