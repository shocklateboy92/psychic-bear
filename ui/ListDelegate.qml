import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

Item {
    property int padding: 10
    property color text_color: palette.text

    id: root

    SystemPalette {
        id: palette
    }

    Rectangle {
        id: highlight
        color: palette.highlight
        anchors.fill: parent
        visible: false
        radius: 2
    }


    Item {
        height: 1
        width: parent.width
        anchors.bottom: parent.bottom

        Rectangle {
            id: bottom_separator
            height: parent.width
            width: 1
            rotation: 90
            anchors.centerIn: parent
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#00000000"
                }

                GradientStop {
                    position: 0.15
                    color: palette.mid
                }
                GradientStop {
                    position: 0.85
                    color: palette.mid
                }

                GradientStop {
                    position: 1
                    color: "#00000000"
                }
            }
        }
    }

    MouseArea {
        id: mouse_area
        hoverEnabled: true
        anchors.fill: parent
    }

    states: [
        State {
            name: "highlighted"
            when: mouse_area.containsMouse
            changes: [
                PropertyChanges {
                    target: highlight
                    visible: true
                },
                PropertyChanges {
                    target: root
                    text_color: palette.highlightedText
                }
            ]
        }
    ]
}

