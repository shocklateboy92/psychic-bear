import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear.ui 1.0
import ".."
import "../attrs"

Module {
    name: "Spells"
    moduleId: "defaultSpells"

    requiredResources: "spel://spellLists/*"

    ListView {
        anchors.fill: parent
        model: matchingResources[0].model

        delegate: Column {
            width: parent.width
//            RowLayout {
//                width: parent.width
////                height: childrenRect.height
//                Component.onCompleted: console.log(width)

                Label {
                    text: "Level # Spells"
                    font.pointSize: 16
//                    Layout.minimumHeight: paintedHeight
                    Layout.fillWidth: true
                }

//                ToolButton {
//                    text: "+"
//                }
//                ToolButton {
//                    text: "-"
//                }

                Repeater {
                    model: modelData
                    delegate: Text {
                        text: "yolo"
                    }
                }
        }
    }
}
