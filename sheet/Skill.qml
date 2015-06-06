import QtQuick 2.0

import org.lasath.psychic_bear 1.0
import "str_utils.js" as StringUtils

Attribute {
    property AbilityScore ability
    property int ranks
    uri: "attr://skills/" + StringUtils.camelize(name)

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
}

