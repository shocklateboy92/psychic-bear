#-------------------------------------------------
#
# Project created by QtCreator 2015-04-27T20:37:48
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = migrate
CONFIG   += console
CONFIG   -= app_bundle
CONFIG 	 += c++14

TEMPLATE = app


SOURCES += main.cpp \
    db-info.cpp

HEADERS += \
    db-info.h

RESOURCES += \
    sql.qrc
