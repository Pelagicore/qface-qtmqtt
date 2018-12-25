#include "shared.h"

{{ module|qt.open_ns }}

Q_LOGGING_CATEGORY(mqttClient, "mqtt.client")
{% for interface in module.interfaces %}
Q_LOGGING_CATEGORY({{interface}}ClientCategory, "{{module}}.{{interface}}Client")
Q_LOGGING_CATEGORY({{interface}}ServiceCategory, "{{module}}.{{interface}}Service")
{% endfor %}

{{ module|qt.close_ns }}
