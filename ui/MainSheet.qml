import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

import org.lasath.psychic_bear 1.0

GroupBox {
    title: "Character Attributes (all) :"
    anchors.margins: 10

    ListView {
        anchors.fill: parent

        model: psychic_bear.all_attributes
        delegate: AttributeDelegate {
           width: parent.width
           attr: modelData
        }
    }
}

