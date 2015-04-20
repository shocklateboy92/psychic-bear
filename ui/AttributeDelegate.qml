import QtQuick 2.0
import QtQuick.Controls 1.2

import org.lasath.psychic_bear 1.0

ListDelegate {
    property Attribute attr

    id: root
    width: text_row.width
    height: text_row.height + padding

    Row {
        id: text_row
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        Label {
            text: attr.value
            font.pointSize: 16
            width: 24
            horizontalAlignment: Text.AlignRight
        }
        Label {
            text: attr.name
            verticalAlignment: Text.AlignVCenter
            height: parent.height
        }
    }
}

