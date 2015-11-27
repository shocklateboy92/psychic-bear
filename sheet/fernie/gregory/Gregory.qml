import QtQuick 2.3

import "qrc:/sheet"
import org.lasath.psychic_bear 1.0

import "qrc:/sheet/shared/feats" as Feats
import "qrc:/sheet/shared/classes" as Classes

Item {
    AbilityScore {
        id: strength
        name: "Strength"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 2
            },
            Bonus {
                source: oldAge
                amount: -3
            }
        ]
    }

    AbilityScore {
        id: dexterity
        name: "Dexterity"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 4
            },
            Bonus {
                source: oldAge
                amount: -3
            }
        ]
    }

    AbilityScore {
        id: constitution
        name: "Constitution"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 4
            },
            Bonus {
                source: oldAge
                amount: -3
            }
        ]
    }

    AbilityScore {
        id: intelligence
        name: "Intelligence"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 6
            },
            Bonus {
                source: race
                amount: 2
            },
            Bonus {
                source: oldAge
                amount: 2
            }
        ]
    }

    AbilityScore {
        id: wisdom
        name: "Wisdom"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 5
            },
            Bonus {
                source: oldAge
                amount: 2
            }
        ]
    }

    AbilityScore {
        id: charisma
        name: "Charisma"
        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: -5
            },
            Bonus {
                source: oldAge
                amount: 2
            }
        ]
    }

    Attribute {
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "Arcanist"
            amount: 3
        }
    }

    Classes.Arcanist {
    }

    Skills {
    }

    Combat {
    }

    BonusSource {
        id: pointBuy
        name: "Point Buy"
    }

    BonusSource {
        id: race
        name: "Race (Human)"
    }

    BonusSource {
        id: oldAge
        name: "Old Age"
    }
}

