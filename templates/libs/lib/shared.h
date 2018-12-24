#pragma once

#include <QtCore>


Q_DECLARE_LOGGING_CATEGORY(mqttClient)
{% for interface in module.interfaces %}
Q_DECLARE_LOGGING_CATEGORY({{interface|lower}}Client)
Q_DECLARE_LOGGING_CATEGORY({{interface|lower}}Service)
{% endfor %}

