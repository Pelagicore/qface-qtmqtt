TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += server_{{module|identifier}}
{% endfor %}

