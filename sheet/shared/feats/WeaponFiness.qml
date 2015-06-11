import QtQuick 2.0

import "../../"
import org.lasath.psychic_bear 1.0

Feat {
    id: weaponFiness
    name: "Weapon Finess"
    conditional: true

    AttributeRef {
        id: attackRef
        targetUri: "attr://combat/meleeAttack"
    }

    AttributeRef {
        id: strengthRef
        targetUri: "attr://abilityScores/strength/temporary/modifier"
    }

    AttributeRef {
        id: dexterityRef
        targetUri: "attr://abilityScores/dexterity/temporary/modifier"
    }

    effects: [
        Bonus {
            id: weaponFinessAttack
            target: attackRef.target
            amount: -strengthRef.target.value + dexterityRef.target.value
        }
    ]
}
