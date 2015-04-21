import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0

Rectangle {
    property Attribute activeAttribute
    GroupBox {
        title: "Character Attributes (all) :"
        anchors.margins: 10
        anchors.fill: parent

        ListView {
            id: listView
            anchors.fill: parent

            FilteredAttributeList {
                id: attribute_list
                pattern: "attr://abilityScores/*/temporary*"
            }
            model: attribute_list.attributes

            delegate: AttributeDelegate {
                width: parent.width
                text: model.name
                value: model.value

                active: activeAttribute == modelData
                onActivationRequest: {
                    activeAttribute = modelData;
                }

                separator_visible: index !== (listView.count - 1)
            }
        }
    }
}
