import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import ".."

Repeater {
    model: source.attributes

    ListDelegate {
        Label {
            id: label
            text: model.value
            font.pointSize: 16
            width: parent.width

            horizontalAlignment: Text.AlignHCenter
        }

        Layout.alignment: Qt.AlignRight
        Layout.fillWidth: true

        height: label.paintedHeight

        onActivationRequest: UiInfo.activeAttribute = modelData
        active: UiInfo.activeAttribute == modelData
    }
}

