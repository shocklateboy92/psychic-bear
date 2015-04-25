import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0

Rectangle {
    property Attribute activeAttribute
    id: scoresArea

    FilteredAttributeList {
        id: perms
        pattern: "attr://abilityScores/*/permanent"
    }
    FilteredAttributeList {
        id: permaMods
        pattern: "attr://abilityScores/*/permanent/modifier"
    }
    FilteredAttributeList {
        id: temps
        pattern: "attr://abilityScores/*/temporary"
    }
    FilteredAttributeList {
        id: tempMods
        pattern: "attr://abilityScores/*/temporary/modifier"
    }

    GroupBox {
        anchors.fill: parent
        anchors.margins: 10

        title: "Ability Scores : "

        GridLayout {
            anchors.fill: parent
            flow: GridLayout.TopToBottom
            rows: 8

            Label {
                text: ""
            }
            Label {
                text: ""
            }

            Repeater {
                model: perms.attributes
                delegate: Label {
                    text: model.name
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                }
            }

            Heading {
                text: "Permanent"
            }

            SubHeading {
                text: "Value"
            }
            ColumnRepeater {
                model: perms.attributes
            }

            SubHeading {
                text: "Modifier"
            }
            ColumnRepeater {
                model: permaMods.attributes
            }

            SubHeading {
                text: "Temporary"
                Layout.columnSpan: 2
            }

            SubHeading {
                text: "Value"
            }
            ColumnRepeater {
                model: temps.attributes
            }

            SubHeading {
                text: "Modifier"
            }
            ColumnRepeater {
                model: tempMods.attributes
            }
        }
    }
}
