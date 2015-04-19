import QtQuick 2.0
import QtQuick.Controls 1.2

ListView {
    Component.onCompleted: {
        for (var v in psychic_bear.all_attributes) {
            console.debug(psychic_bear.all_attributes[v]);
        }
    }
}

