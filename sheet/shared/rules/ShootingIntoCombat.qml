import QtQuick 2.0

import org.lasath.psychic_bear 1.0

BonusSource {
    uri: "msrc://rules/combat/penalties/shootingIntoCombat"
    name: "Shooting Into Combat"
    conditional: true

    effects: [
        Bonus {
            amount: -4
            target: rangedAttackRef.target
        }
    ]

    AttributeRef {
        id: rangedAttackRef
        targetUri: "attr://combat/baseAttackBonus/ranged"
    }
}
