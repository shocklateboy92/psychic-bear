import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    GroupBox {
        anchors.fill: parent
        anchors.margins: 10

        title: "All Conditions"

        ListView {
            anchors.fill: parent
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            model: psychic_bear.all_bonus_sources

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
