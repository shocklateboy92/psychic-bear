import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import "ui"

ApplicationWindow {
    id: root
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
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        AttributesView {
            id: sheet
            width: root.width /3

            name: "Ability Scores : "
            filterPattern: "attr://abilityScores/*"

            onActiveAttributeChanged: {
                modifiers_view.targetAttribute = activeAttribute;
            }
        }
        AttributesView {
            width: root.width /3

            name: "Skills : "
            filterPattern: "attr://skills/*"

            onActiveAttributeChanged: {
                modifiers_view.targetAttribute = activeAttribute;
            }
        }

        ModifiersView {
            id: modifiers_view
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
