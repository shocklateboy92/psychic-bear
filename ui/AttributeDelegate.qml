import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0

ListDelegate {
    property string text
    property int value
    property bool strikeout: false

    id: root
    height: text_row.height + padding

    FontMetrics {
        id: labelMetrics
        font: valueLabel.font
    }

    RowLayout {
        id: text_row
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        spacing: labelMetrics.averageCharacterWidth * 0.75

        Label {
            id: valueLabel
            text: root.value
            font.pointSize: Qt.platform.os == "android" ? 24 : 16
            horizontalAlignment: Text.AlignRight
            font.strikeout: root.strikeout

            Layout.minimumWidth: labelMetrics.averageCharacterWidth * 4
        }
        Label {
            text: root.text
            verticalAlignment: Text.AlignVCenter
            height: parent.height
            font.strikeout: root.strikeout
            Layout.fillWidth: true
        }
    }
}

