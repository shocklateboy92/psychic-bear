import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0

import ".."

Module {
    property Attribute targetAttribute: UiInfo.activeAttribute

    name: "Current Attribute Details"
    moduleId: "attributeDetails"

    ColumnLayout {
        anchors.margins: 10
        anchors.fill: parent

        Label {
            Layout.fillWidth: true

            font.pointSize: 16
            wrapMode: Text.Wrap
            horizontalAlignment: "AlignRight"

            text: targetAttribute.name
        }
        Label {
            Layout.fillWidth: true

            font.pointSize: 12
            wrapMode: Text.Wrap
            horizontalAlignment: "AlignRight"

            text: targetAttribute.value
        }

        GroupBox {
            title: "Attribute Modifiers :"
            Layout.fillHeight: true
            Layout.fillWidth: true
            implicitWidth: parent.width
            implicitHeight: 36

            ListView {
                id: attributeList
                anchors {
                    top: parent.top
                    bottom: attributeNewModifier.top
                    left: parent.left
                    right: parent.right
                }

                clip: true
                boundsBehavior: Flickable.StopAtBounds

                model: targetAttribute.modifiers
                delegate: AttributeDelegate {
                    width: parent.width

                    text: model.name
                    value: model.amount
                    strikeout: model.source && !model.source.active
                }
            }

            GridLayout {
                property bool editing: false

                id: attributeNewModifier
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                visible: !targetAttribute.readOnly

                columns: 2
                Button {
                    visible: !attributeNewModifier.editing
                    Layout.fillWidth: true

                    text: "New Static Modifier"
                    onClicked: attributeNewModifier.editing = true
                }
                Label {
                    visible: attributeNewModifier.editing
                    text: "Amount: "
                }
                SpinBox {
                    id: amountSpinner
                    visible: attributeNewModifier.editing
                    minimumValue: -9000

                    Keys.onEscapePressed: {
                        attributeNewModifier.editing = false;
                    }
                }

                Label {
                    visible: attributeNewModifier.editing
                    text: "Description: "
                }
                TextField {
                    id: descText
                    visible: attributeNewModifier.editing
                    Layout.fillWidth: true
                    placeholderText: "Press Enter to accept"

                    onAccepted: {
                        if (amountSpinner.value == 0 || this.text.length === 0) {
                            console.log("Static modifiers must have a non-zero value and a description");
                            return;
                        }

                        targetAttribute.createStaticModifier(amountSpinner.value, this.text);
                        attributeNewModifier.editing = false;
                    }
                    Keys.onEscapePressed: {
                        attributeNewModifier.editing = false;
                    }
                }

                onEditingChanged: {
                    descText.text = "";
                    amountSpinner.forceActiveFocus();
                }
            }
        }
    }
}
