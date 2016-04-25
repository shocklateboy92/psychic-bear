import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0

Module {
    name: "Ability Scores"
    moduleId: "abilityScores"

    ResourceFilter {
        id: perms
        uriFilter: "attr://abilityScores/*/permanent"
    }
    ResourceFilter {
        id: permaMods
        uriFilter: "attr://abilityScores/*/permanent/modifier"
    }
    ResourceFilter {
        id: temps
        uriFilter: "attr://abilityScores/*/temporary"
    }
    ResourceFilter {
        id: tempMods
        uriFilter: "attr://abilityScores/*/temporary/modifier"
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10

        flow: GridLayout.TopToBottom
        rows: 22

        Label {
            text: ""
        }
        Label {
            text: ""
        }

        Repeater {
            model: perms
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
            model: perms
        }

        SubHeading {
            text: "Modifier"
        }
        ColumnRepeater {
            model: permaMods
        }

        Heading {
            text: "Temporary"
        }

        SubHeading {
            text: "Value"
        }
        ColumnRepeater {
            model: temps
        }

        SubHeading {
            text: "Modifier"
        }
        ColumnRepeater {
            model: tempMods
        }
    }
}
