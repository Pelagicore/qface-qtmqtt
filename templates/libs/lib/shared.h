#pragma once

#include <QtCore>

{{ module|qt.open_ns }}

Q_DECLARE_LOGGING_CATEGORY(mqttClient)
{% for interface in module.interfaces %}
Q_DECLARE_LOGGING_CATEGORY({{interface}}ClientCategory)
Q_DECLARE_LOGGING_CATEGORY({{interface}}ServiceCategory)
{% endfor %}

{{ module|qt.close_ns }}

