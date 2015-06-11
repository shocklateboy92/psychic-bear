import QtQuick 2.0

import "../../"
import org.lasath.psychic_bear 1.0

Feat {
    id: powerAttack
    name: "Power Attack"
    conditional: true

    AttributeRef {
        id: babRef
        targetUri: "attr://combat/baseAttackBonus"
    }

    AttributeRef {
        id: attackRef
        targetUri: "attr://combat/meleeAttack"
    }

    AttributeRef {
        id: damageRef
        targetUri: "attr://combat/meleeDamage"
    }

    effects: [
        Bonus {
            id: powerAttackAttack
            target: attackRef.target
            amount: Math.floor((babRef.target.value / 4) + 1) * -1
        },
        Bonus {
            id: powerAttackDamage
            target : damageRef.target
            amount: Math.floor((babRef.target.value / 4) + 1) * 2
        }
    ]
}
