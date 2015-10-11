import QtQuick 2.0
import QtQuick.Controls 1.2

import org.lasath.psychic_bear 1.0

ListDelegate {
    property string text
    property int value
    property bool strikeout: false

    id: root
    width: text_row.width
    height: text_row.height + padding

    Row {
        id: text_row
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        Label {
            text: root.value
            font.pointSize: 16
            width: 36
            horizontalAlignment: Text.AlignRight
            font.strikeout: root.strikeout
        }
        Label {
            text: root.text
            verticalAlignment: Text.AlignVCenter
            height: parent.height
            font.strikeout: root.strikeout
        }
    }
}

