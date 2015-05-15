import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import "ui"
import "ui/scores"

ApplicationWindow {
    id: root
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    visibility: Window.Maximized

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

        SplitView {
            orientation: Qt.Vertical
            width: root.width /4

            AbilityScoresArea {
                id: sheet
                height: parent.height / 4

                onActiveAttributeChanged: {
                    modifiers_view.targetAttribute = activeAttribute;
                }
            }

            AttributesView {

                name: "Combat Stats : "
                filterPattern: "attr://combat/*"

                onActiveAttributeChanged: {
                    modifiers_view.targetAttribute = activeAttribute;
                }
            }


        }
        AttributesView {
            width: root.width /4

            name: "Skills : "
            filterPattern: "attr://skills/*"

            onActiveAttributeChanged: {
                modifiers_view.targetAttribute = activeAttribute;
            }
        }

        ConditionsView {
            width: root.width /4
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
