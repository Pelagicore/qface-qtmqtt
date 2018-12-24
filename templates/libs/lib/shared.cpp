#include "shared.h"

Q_LOGGING_CATEGORY(mqttClient, "mqtt.client")
{% for interface in module.interfaces %}
Q_LOGGING_CATEGORY({{interface|lower}}Client, "{{module}}.{{interface}}Client")
Q_LOGGING_CATEGORY({{interface|lower}}Service, "{{module}}.{{interface}}Service")
{% endfor %}
