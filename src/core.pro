TEMPLATE = lib
TARGET = core
QT += qml quick sql
CONFIG += c++11

TARGET = $$qtLibraryTarget($$TARGET)
#uri = org.lasath.psychic_bear

DEFINES += PB_CORE_LIBRARY

# Input
SOURCES += *.cpp
HEADERS += *.h

unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    target.path = $$installPath
    INSTALLS += target
}
