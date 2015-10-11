import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0

import ".."

Module {

    GroupBox {
        id: groupbox
        anchors.margins: 10
        anchors.fill: parent
        title: name

        ListView {
            id: listView
            anchors.fill: parent
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            model: matchingResources

            delegate: AttributeDelegate {
                width: parent.width
                text: model.name
                value: model.value

                active: UiInfo.activeAttribute == modelData
                onActivationRequest: UiInfo.activeAttribute = modelData

                separator_visible: index !== (listView.count - 1)
            }
        }
    }
}
