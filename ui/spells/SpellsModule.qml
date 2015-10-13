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
        anchors.margins: 10
        model: matchingResources

        delegate: Column {
            width: parent.width
            spacing: 5

            Label {
                text: modelData.name
                font.pointSize: 16
                Layout.fillWidth: true
            }

            GroupBox {
                width: parent.width

                Column {
                    Repeater {
                        model: modelData.model
                        delegate: Text {
                            text: model.name
                        }
                    }
                    ToolButton {
                        text: "+"
                    }
                }
            }
        }
    }
}
