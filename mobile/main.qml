import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import "qrc:/ui/scores"
import "qrc:/ui/attrs"
import "qrc:/ui/info"
import "qrc:/ui/conds"

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("&Back")
                onTriggered: stack.pop()
            }

            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    property list<Item> modules
    modules: [
        AbilityScoresModule {
            id: asm
        },
        CombatAttributesModule {
            id: cam
        },
        SkillAttributesModule {
            id: sam
        },
        AttributeInfoModule {
            id: aim
        },
        ConditionsModule {
            id: cm
        }
    ]

    StackView {
        id: stack
        anchors.fill: parent

        initialItem: Column {
            width: parent.width
            Repeater {
                model: modules
                delegate: Button {
                    width: parent.width

                    text: model.name

                    onClicked: stack.push(model.modelData)
                }
            }
        }
    }
}
