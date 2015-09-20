import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Skill {
    modifiers: [
        Bonus {
            name: "Class Skill"
            // Class skill (aptitude) doesn't apply unless already trained
            amount: ranks > 0 ? 3 : 0
        }
    ]
}

