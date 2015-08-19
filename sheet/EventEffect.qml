import QtQuick 2.0
import org.lasath.psychic_bear 1.0

Item {
    property Attribute target
    property int modifier: 0
    property bool isBounded: false
    property int bound

    function dothing () {
        if (isBounded){
            target.createStaticModifier()
        }
        //Bound +ve -> target approaches bound
        //Bound -ve -> target approaches bound

        target.createStaticModifier(modifier, parent.name)
    }
}

