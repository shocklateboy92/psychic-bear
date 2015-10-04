import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Item {
    function getSpellsPerDayOf(spellLevel, casterLevel) {
        if (spellLevel === 1) {
            casterLevel += 1;
        }

        if (Math.floor(casterLevel / 2) >= spellLevel) {
            return Math.min(casterLevel - (spellLevel * 2) + 2, 4);
        }

        return 0;
    }

    Component.onCompleted: {
//        console.log(Math.ceil(1 / 2));
        for (var j = 1; j < 20; j++) {
//            var str = j + ": ";
            var str = "";
            for (var i = 1; i < 9; i++) {
                str += getSpellsPerDayOf(i, j) + " ";
            }
            console.log(str);
        }
    }
}
