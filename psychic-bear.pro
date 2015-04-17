TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    src/attribute.cpp \
    src/bonus.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/attribute.h \
    src/bonus.h
