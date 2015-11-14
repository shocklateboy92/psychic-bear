import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0
import ".."

Module {
    name: "Spells"
    moduleId: "defaultSpells"

    requiredResources: "spel://spellLists/*"

    ListView {
        anchors.fill: parent
        anchors.margins: 10
        model: matchingResources

        delegate: Column {
            property SpellList spellList: modelData

            width: parent.width
            spacing: 5

            Label {
                text: spellList.name
                font.pointSize: 16
                wrapMode: Text.Wrap
                width: parent.width
            }

            GroupBox {
                width: parent.width

                Column {
                    width: parent.width

                    Repeater {
                        model: spellList.model

                        delegate: ListDelegate {
                            property bool editing: false
                            id: listDelegate

                            width: parent.width
                            height: row.height

                            FontMetrics {
                                id: titleMetrics
                                font: titleLabel.font
                            }

                            RowLayout {
                                id: row
                                width: parent.width
                                height: titleMetrics.height + 10

                                // Non-editing (display) stuff
                                Label {
                                    id: titleLabel
                                    visible: !editing
                                    Layout.alignment: Qt.AlignVCenter

                                    text: model.name ? model.name : "Unused Spell Slot"
                                    font.pointSize: 12
                                }
                                Label {
                                    visible: !editing
                                    Layout.alignment: Qt.AlignLeft
                                    Layout.fillWidth: true
                                    Layout.minimumWidth: 0

                                    text: model.short_description.trim()
                                    elide: Text.ElideRight
                                }
                                Button {
                                    visible: !editing && listDelegate.active
                                    onClicked: editing = !editing

                                    text: "Edit"
                                    Layout.rightMargin: 10
                                }

                                // Editing stuff
                                ComboBox {
                                    visible: editing
                                    Layout.fillWidth: true
                                    Layout.leftMargin: 5

                                    textRole: "name"
                                    model: spellList.model
                                }
                                Button {
                                    visible: editing
                                    Layout.rightMargin: 5

                                    text: "Remove"
                                    onClicked: spellList.removeSlot(index)
                                }
                            }

                            onActivationRequest: active = !active
                        }
                    }
                    ToolButton {
                        text: "+"
                        onClicked: spellList.createNewSlot()
                    }
                }
            }
        }
    }
}
