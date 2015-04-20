import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

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
    }
}
