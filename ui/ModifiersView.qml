import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2

import org.lasath.psychic_bear 1.0

Rectangle {
    property Attribute targetAttribute

    GroupBox {
        title: "Attribute Modifiers :"
        anchors.margins: 10
        anchors.fill: parent

        ListView {
            anchors.fill: parent

            model: targetAttribute.modifiers
            delegate: AttributeDelegate {
                width: parent.width

                text: model.name
                value: model.amount
            }
        }

        Button {
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            visible: !targetAttribute.readOnly
            text: "New Static Modifier"
            onClicked: {
                new_mod_dialog.open();
            }
        }
    }

    onTargetAttributeChanged: {
        targetAttribute.updateStaticModifiers();
    }

    Dialog {
        id: new_mod_dialog
        width: 450
        standardButtons: StandardButton.Ok | StandardButton.Cancel

        NewModifierDialog {
            id: content
            anchors.centerIn: parent
        }

        onAccepted: {
            if (content.amount == 0 || content.description.length == 0) {
                console.log("Static modifiers must have a non-zero value and a description");
                return;
            }

            targetAttribute.createStaticModifier(content.amount, content.description);
        }
    }
}
