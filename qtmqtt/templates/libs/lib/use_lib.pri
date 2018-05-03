QT += core
QT += qml
QT += mqtt

LIBS += -L$$BUILD_DIR/libs
LIBS += -llib_{{module|identifier}}

INCLUDEPATH += $$PWD

