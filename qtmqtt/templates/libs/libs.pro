TEMPLATE = subdirs

{% for module in system.modules %}
SUBDIRS += lib_{{module|identifier}}
{% endfor %}
