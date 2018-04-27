TEMPLATE = lib
TARGET = lib_{{module|identifier}}
DESTDIR = $$BUILD_DIR/libs

CONFIG += staticlib
CONFIG += c++11

QT += core
QT += qml


OTHER_FILES += use_lib_{{module|identifier}}.pri

