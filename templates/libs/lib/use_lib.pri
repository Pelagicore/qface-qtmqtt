QT += core
QT += qml
QT += qmqtt

LIBS += -L$$BUILD_DIR/libs
LIBS += -llib_{{module|identifier}}

INCLUDEPATH += $$PWD

