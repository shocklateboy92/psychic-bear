import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Attribute {
    property AbilityScore ability
    property bool primary
    property int magicModifier
    property int miscModifier
    property int tempModifier
    uri: "attr://savingThrows/" + camelize(name)

    modifiers: [
        Bonus {
            name: ability.temporary.modifier.name
            amount: ability.temporary.modifier.value
        },
        Bonus {
            name: "Ranks"
            amount: ranks
        },
        Bonus {
            name: "Base"
            bonus: primary ?
                       Math.floor((level.value / 2) + 2) :
                       Math.floor(level.value / 3)
        }
    ]

    function camelize(str) {
        return str.replace(/[^\w\s]+/g, '').replace(
                    /(?:^\w|[A-Z]|\b\w)/g, function(letter, index) {
                        return index === 0 ? letter.toLowerCase() : letter.toUpperCase();
                    }).replace(/\s+/g, '');
    }
}

