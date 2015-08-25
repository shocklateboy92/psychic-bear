QT += qml quick widgets sql
CONFIG += c++14 qml_debug

QMAKE_CXXFLAGS += -Wall

SOURCES += \
    db.cpp \
    app-main.cpp

RESOURCES += qml.qrc \
    sheet/character.qrc \
    ui/ui.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS +=  db.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/src/release/ -lcored
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/src/debug/ -lcored
else:unix: LIBS += -L$$OUT_PWD/src/ -lcore

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
