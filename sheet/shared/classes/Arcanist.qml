import QtQuick 2.3

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

    function getBonusSpellsPerDayOf(spellLevel, abilityModifier) {
        return Math.max(Math.ceil((abilityModifier - spellLevel + 1) / 4), 0);
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

    Instantiator {
        model: [1,2,3,4,5,6,7,8,9]

        Attribute {
            name: "Level " + modelData + " Spells Per Day (Total)"
            uri: "attr://spells/castsPerDay/total/" + modelData

            modifiers: [
                Bonus {
                    name: "Arcanist Base"
                    amount: getSpellsPerDayOf(modelData, levelRef.target.value)
                },
                Bonus {
                    name: "Bonus Spells (INT)"
                    amount: getBonusSpellsPerDayOf(modelData, intRef.target.value)
                }
            ]
        }
    }

    AttributeRef {
        id: levelRef
        targetUri: "attr://level"
    }
    AttributeRef {
        id: intRef
        targetUri: "attr://abilityScores/intelligence/permanent/modifier"
    }
}
