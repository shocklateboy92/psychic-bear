import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0

Module {
    name: "Ability Scores"
    moduleId: "abilityScores"

    FilteredResourceList {
        id: perms
        pattern: "attr://abilityScores/*/permanent"
    }
    FilteredResourceList {
        id: permaMods
        pattern: "attr://abilityScores/*/permanent/modifier"
    }
    FilteredResourceList {
        id: temps
        pattern: "attr://abilityScores/*/temporary"
    }
    FilteredResourceList {
        id: tempMods
        pattern: "attr://abilityScores/*/temporary/modifier"
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10

        flow: GridLayout.TopToBottom
        rows: 8

        Label {
            text: ""
        }
        Label {
            text: ""
        }

        Repeater {
            model: perms.matches
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
            model: perms.matches
        }

        SubHeading {
            text: "Modifier"
        }
        ColumnRepeater {
            model: permaMods.matches
        }

        SubHeading {
            text: "Temporary"
            Layout.columnSpan: 2
        }

        SubHeading {
            text: "Value"
        }
        ColumnRepeater {
            model: temps.matches
        }

        SubHeading {
            text: "Modifier"
        }
        ColumnRepeater {
            model: tempMods.matches
        }
    }
}
