import QtQuick 2.0

import "../../"
import org.lasath.psychic_bear 1.0

Feat {
    id: powatt
    name: "Power Attack"
    conditional: true

    AttributeRef {
        id: baseAttack
        targetUri: "attr://combat/baseAttackBonus"
    }

    AttributeRef {
        id: toHit
        targetUri: "attr://combat/baseAttackBonus/melee/tohit"
    }

    AttributeRef {
        id: meleeDamage
        targetUri: "attr://combat/baseAttackBonus/melee/damagebonus"
    }

    effects: [
        Bonus {
            id: powattToHit
            target: toHit.target
            amount: Math.min(-1, -1 + ((baseAttack.target.value/4)*-1))
        },
        Bonus {
            id: powattMeleeBonus
            target: meleeDamage.target
            amount: Math.max(2, 2 + ((baseAttack.target.value/4)*2))
        }
    ]

    property int powerAttackMeleeBonus: powattMeleeBonus.amount
}


