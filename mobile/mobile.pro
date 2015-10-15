TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp \
           ../app/ui-module.cpp

HEADERS += ../app/ui-module.h

RESOURCES += qml.qrc ../ui/ui.qrc \
    ../sheet/character.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug -lcored
else:unix: LIBS += -L$$OUT_PWD/../src/ -lcore

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src
