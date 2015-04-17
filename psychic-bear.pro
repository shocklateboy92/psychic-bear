TEMPLATE = app

QT += qml quick widgets
CONFIG += c++14

QMAKE_CXXFLAGS += -Wall

SOURCES += main.cpp \
    src/attribute.cpp \
    src/bonus.cpp \
    src/attribute-manager.cpp \
    bonus-source.cpp

RESOURCES += qml.qrc \
    sheet/character.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/attribute.h \
    src/bonus.h \
    src/attribute-manager.h \
    bonus-source.h
