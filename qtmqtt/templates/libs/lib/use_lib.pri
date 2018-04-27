QT += core
QT += qml

LIBS += -L$$BUILD_DIR/libs
LIBS += -llib_{{module|identifier}}

INCLUDEPATH += $$PWD

