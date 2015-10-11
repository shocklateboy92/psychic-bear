QT += qml quick widgets sql quickwidgets
CONFIG += c++14 qml_debug

QMAKE_CXXFLAGS += -Wall

SOURCES += \
    db.cpp \
    app/ui-module.cpp \
    app/container-window.cpp \
    app/app-main.cpp

RESOURCES += \
    sheet/character.qrc \
    ui/ui.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS +=  db.h \
    app/container-window.h \
    app/ui-module.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/src/release/ -lcored
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/src/debug/ -lcored
else:unix: LIBS += -L$$OUT_PWD/src/ -lcore

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
