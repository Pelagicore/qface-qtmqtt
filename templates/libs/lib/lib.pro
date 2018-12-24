TEMPLATE = lib
TARGET = lib_{{module|identifier}}
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += core
QT += qml
QT += qmqtt

HEADERS += mqttclient.h
SOURCES += mqttclient.cpp

HEADERS += {{module.module_name|lower}}shared.h
SOURCES += {{module.module_name|lower}}shared.cpp

{% for interface in module.interfaces %}
HEADERS += {{interface|lower}}client.h
SOURCES += {{interface|lower}}client.cpp

HEADERS += abstract{{interface|lower}}service.h
SOURCES += abstract{{interface|lower}}service.cpp
{% endfor %}

HEADERS += variantmodel.h
SOURCES += variantmodel.cpp

OTHER_FILES += use_lib_{{module|identifier}}.pri
