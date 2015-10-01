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
        pattern: "attr://abilityScores/*/permanent"
        onMatchesChanged: readyInput(this)
    }
    ResourceFilter {
        id: permaMods
        pattern: "attr://abilityScores/*/permanent/modifier"
        onMatchesChanged: readyInput(this)
    }
    ResourceFilter {
        id: temps
        pattern: "attr://abilityScores/*/temporary"
        onMatchesChanged: readyInput(this)
    }
    ResourceFilter {
        id: tempMods
        pattern: "attr://abilityScores/*/temporary/modifier"
        onMatchesChanged: readyInput(this)
    }

    Component {
        id: component_GridLayout
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


    /*
     * There's a stupid bug that makes the layout manager (GridLayout)
     * freak out when new elements are added after initial rendering
     * (from the repeaters).
     *
     * So this is a shitty workaround causing the ability scores grid
     * to wait until all the models have data in them before actually
     * rendering.
     *
     */
    Loader {
        id: loader_GridLayout
        anchors.fill: parent
        sourceComponent: component_GridLayout

        property int requiredSources: 4
        active: requiredSources <= 0
    }

    function readyInput(source) {
        if (source.matches.length > 0) {
            loader_GridLayout.requiredSources--;
        }
    }
}
