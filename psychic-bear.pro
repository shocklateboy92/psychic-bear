TEMPLATE = app

QT += qml quick widgets sql
CONFIG += c++14

QMAKE_CXXFLAGS += -Wall

SOURCES += main.cpp \
    src/attribute.cpp \
    src/bonus.cpp \
    src/attribute-manager.cpp \
    src/bonus-source.cpp \
    src/project-context.cpp \
    db.cpp \
    src/db-attribute.cpp

RESOURCES += qml.qrc \
    sheet/character.qrc \
    ui/ui.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/attribute.h \
    src/bonus.h \
    src/attribute-manager.h \
    src/bonus-source.h \
    src/project-context.h \
    db.h \
    src/db-attribute.h
