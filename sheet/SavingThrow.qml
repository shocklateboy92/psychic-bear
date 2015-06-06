import QtQuick 2.0

import org.lasath.psychic_bear 1.0
import "str_utils.js" as StringUtils

Attribute {
    property AbilityScore ability
    property bool primary
    uri: "attr://combat/savingThrows/" + StringUtils.camelize(name)

    modifiers: [
        Bonus {
            name: "Base"
            amount: primary ?
                       Math.floor((level.value / 2) + 2) :
                       Math.floor(level.value / 3)
        },
        Bonus {
            name: ability.temporary.modifier.name
            amount: ability.temporary.modifier.value
        }
    ]
}

