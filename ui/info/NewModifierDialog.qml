import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import org.lasath.psychic_bear 1.0

Item {
    height: 45
    width: 400

    property alias description: text_field.text
    property alias amount: spinner.value

    RowLayout {
        id: rowLayout1
        anchors.fill: parent

        Label {
            text: qsTr("Amount :")
        }

        SpinBox {
            id: spinner
            Layout.fillWidth: true
            minimumValue: -9000
        }

        Label {
            text: qsTr("Description :")
        }

        TextField {
            id: text_field
            Layout.fillWidth: true
        }
    }
}
