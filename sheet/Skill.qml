import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Attribute {
    property AbilityScore ability
    property int ranks
    uri: "attr://skills/" + camelize(name)

    modifiers: [
        Bonus {
            name: ability.temporary.modifier.name
            amount: ability.temporary.modifier.value
        },
        Bonus {
            name: "Ranks"
            amount: ranks
        }
    ]

    function camelize(str) {
        return str.replace(/(?:^\w|[A-Z]|\b\w)/g, function(letter, index) {
            return index === 0 ? letter.toLowerCase() : letter.toUpperCase();
        }).replace(/\s+/g, '');
    }
}

