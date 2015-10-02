import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear.ui 1.0
import ".."

Item {
    property alias model: actionsListView.model
    property alias title: titleLabel.text

    ColumnLayout {
        anchors.fill: parent

        Label {
            id: titleLabel
            Layout.fillWidth: true

            font.pointSize: 16
            horizontalAlignment: Text.AlignRight
        }

        GroupBox {
            anchors.margins: 10
            Layout.fillHeight: true
            width: parent.width

            ListView {
                id: actionsListView
                anchors.fill: parent

                delegate: RowLayout {
                    width: parent.width

                    CheckBox {
                        id: acceptCheckBox
                        height: parent.height
                    }

                    AttributeDelegate {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        width: parent.width

                        text: modelData.attribute
                        value: modelData.amount

                        onActivationRequest: {
                            acceptCheckBox.checked = !acceptCheckBox.checked;
                        }
                    }
                }
            }
        }

        Button {
            id: acceptButton
            Layout.fillWidth: true

            text: "Create Static Modifiers"
        }
    }
}
