#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T23:35:05
#
#-------------------------------------------------

QT       += core sql quick
QT       -= gui

TARGET = init-db
CONFIG   += console
CONFIG   -= app_bundle
CONFIG 	 += c++14

TEMPLATE = app


SOURCES += main.cpp

RESOURCES += ../../sheet/character.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release/ -lcored
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug/ -lcored
else:unix: LIBS += -L$$OUT_PWD/../../src/ -lcore

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src
