TEMPLATE = app
QT += core
QT -= gui

CONFIG += c++11

DESTDIR = $$BUILD_DIR/bin
TARGET = {{module}}_server
CONFIG += console
macos {
    CONFIG -= app_bundle
}

SOURCES += main.cpp

{% for interface in module.interfaces %}
HEADERS += {{interface|lower}}service.h
SOURCES += {{interface|lower}}service.cpp
{% endfor %}

include( $$SOURCE_DIR/libs/lib_{{module|identifier}}/use_lib_{{module|identifier}}.pri )



