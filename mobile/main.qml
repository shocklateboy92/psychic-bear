import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import "qrc:/ui/scores"
import "qrc:/ui/attrs"
import "qrc:/ui/info"
import "qrc:/ui/conds"
import "qrc:/ui/spells"
import "qrc:/ui"

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
        AbilityScoresModule {},
        CombatAttributesModule {},
        SkillAttributesModule {},
        AttributeInfoModule {
            id: infoModule
        },
        ConditionsModule {},
        PreparedSpellsModule {},
        SpontaneousSpellsModule {},
        CastingAttributesModule {}
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

        focus: true
        Keys.onReleased: {
            if (event.key === Qt.Key_Back && stack.depth > 1) {
                stack.pop();
                event.accepted = true;
            }
        }
    }

    Connections {
        target: UiInfo
        onActiveAttributeChanged: {
            stack.push(infoModule);
        }
    }
}
