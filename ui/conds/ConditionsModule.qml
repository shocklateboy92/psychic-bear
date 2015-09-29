import QtQuick 2.3
import QtQuick.Controls 1.2

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0

Module {
    name: "All Conditions"
    moduleId: "conditions"
    requiredResources: "msrc://*"

    GroupBox {
        anchors.fill: parent
        anchors.margins: 10

        title: name

        ListView {
            anchors.fill: parent
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            model: matchingResources

            delegate: Button {
                width: parent.width

                checkable: true
                text: model.name

                checked: model.active
                Binding {
                    target: modelData
                    property: "active"
                    value: checked
                }
                enabled: model.conditional
            }
        }
    }
}
