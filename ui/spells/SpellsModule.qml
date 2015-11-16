import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0
import org.lasath.psychic_bear.ui 1.0
import ".."

Module {
    property ListDelegate activeDelegate

    name: "Spells"
    moduleId: "defaultSpells"

    requiredResources: "spel://spellLists/*"

    ListView {
        anchors.fill: parent
        anchors.margins: 10
        model: matchingResources
        spacing: 10

        delegate: Column {
            property SpellList spellList: modelData

            width: parent.width
            spacing: 5

            Label {
                text: spellList.name
                font.pointSize: 16
                wrapMode: Text.Wrap
                width: parent.width
                horizontalAlignment: Text.AlignLeft
            }

            GroupBox {
                width: parent.width
                title: "Cast: 3, Remaning: 4, Save DC: 15"

                Column {
                    width: parent.width

                    Repeater {
                        id: listRepeater
                        model: spellList.model

                        delegate: ListDelegate {
                            property bool editing: false

                            id: listDelegate

                            width: parent.width
                            height: row.height + 10

                            active: activeDelegate === this
                            onActivationRequest: {
                                if (active) {
                                    activeDelegate = null;
                                } else {
                                    activeDelegate = this;
                                }
                            }

                            separator_visible: index < listRepeater.count - 1

                            FontMetrics {
                                id: titleMetrics
                                font: titleLabel.font
                            }

                            ColumnLayout {
                                id: row
                                width: parent.width - 10
                                spacing: 0

                                anchors.centerIn: parent

                                // Non-editing (display) stuff
                                Label {
                                    id: titleLabel
                                    visible: !editing

                                    text: model.name ? model.name : "Unused Spell Slot"
                                    font.bold: true
                                }
                                Label {
                                    visible: !editing
                                    Layout.fillWidth: true

                                    wrapMode: Text.Wrap
                                    text: model.short_description ?
                                              model.short_description.trim() : ""

                                    elide: Text.ElideRight
                                    maximumLineCount: listDelegate.active ? 20 : 1
                                }
                                Row {
                                    visible: !editing && listDelegate.active

                                    ToolButton {
                                        text: "Details"
                                        onClicked: Qt.openUrlExternally(model.linktext)
                                    }

                                    ToolButton {
                                        text: "Cast"
                                    }

                                    ToolButton {
                                        onClicked: editing = !editing

                                        text: "Edit"
                                    }
                                    Layout.alignment: Qt.AlignRight
                                }

                                // Editing stuff
                                ComboBox {
                                    visible: editing
                                    Layout.fillWidth: true
                                    Layout.leftMargin: 5

                                    textRole: "name"
                                    model: spellList.availableSpells

                                    editable: true
                                    onAccepted: {
                                        spellList.updateSpellSlot(
                                                    index,
                                                    model.getIdOf(
                                                        currentIndex
                                                        )
                                                    );
                                        editing = false;
                                    }

                                    Keys.onEscapePressed: {
                                        editing = false;
                                    }

                                    onVisibleChanged: {
                                        currentIndex = find(titleLabel.text);
                                        selectAll();
                                        forceActiveFocus();
                                    }
                                }

                                // We'll put this button back once the functionality
                                // has been implemented.
//                                Button {
//                                    visible: editing
//                                    Layout.rightMargin: 5

//                                    text: "Remove"
//                                    onClicked: spellList.removeSlot(index)
//                                }
                            }
                        }
                    }
                }
            }

            ToolButton {
                anchors.right: parent.right
                text: "Create New Slot"
                onClicked: spellList.createNewSlot()
            }
        }
    }
}
