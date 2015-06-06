import QtQuick 2.0

import "../../"
import org.lasath.psychic_bear 1.0

Feat {
    id: tset
    name: "Toughness"

    AttributeRef {
        id: hpRef
        targetUri: "attr://combat/hitPoints/maximum"
    }
    AttributeRef {
        id: levelRef
        targetUri: "attr://level"
    }

    effects: [
        Bonus {
            id: yolo
            target: hpRef.target
            amount: Math.max(3, levelRef.target.value)
        }
    ]
}

