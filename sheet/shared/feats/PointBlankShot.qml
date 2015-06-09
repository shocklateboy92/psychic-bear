import QtQuick 2.0

import "../../"
import org.lasath.psychic_bear 1.0

Feat {
    id: tset
    name: "Point Blank Shot (Combat)"
    //description: "Benefit: You get a +1 bonus on attack and damage rolls with ranged weapons at ranges of up to 30 feet."
    //rangeInFeet: 30
    //range:
    conditional: true

    AttributeRef {
        id: rangedAttackBonusRef
        targetUri: "attr://combat/baseAttackBonus/ranged"
    }

    effects: [
        Bonus {
            target: rangedAttackBonusRef.target
            amount: 1
        }
    ]
}

