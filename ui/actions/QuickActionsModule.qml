import QtQuick 2.3
import QtQuick.Controls 1.2

import org.lasath.psychic_bear.ui 1.0

Module {
    name: "Quick Actions"
    moduleId: "actions"

    anchors.margins: 10
    GroupBox {

    ToolButton {
        id: backButton
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
//            margins: 10
        }
        width: 0

        text: "<"
        onClicked: stack.pop();

        states: [
            State {
                name: "shown"
                when: stack.depth > 1
                PropertyChanges {
                    target: backButton
                    visible: true
                    width: 24
                }
            }
        ]
    }
        title: "Available Actions :"
        anchors.fill: parent
        anchors.margins: 10
        clip: true


        StackView {
            id: stack
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: backButton.right
                right: parent.right
//                margins: 10
//                leftMargin: 0
            }
//            anchors.fill: parent
//            anchors.margins: 10

            initialItem: ListView {

                width: parent.width
                height: parent.height

                model: dummyData

                delegate: Button {
                    text: modelData.name
                    width: parent.width
                    onClicked: {
                        stack.push({
                                       item: Qt.resolvedUrl("ActionsView.qml"),
                                       properties: {
                                           title: modelData.name,
                                           model: modelData.actions
                                       }
                                   });
                    }
                }
            }
        }
    }

    property var dummyData: [
        {
            name: "8 Hours Rest",
            actions: [
                {
                    attribute: "Current Hit Points",
                    amount: 3
                }
            ]
        }
    ]
}
