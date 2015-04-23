import QtQuick 2.3
import org.lasath.psychic_bear 1.0

Item {
	AbilityScore {
		id: strength
		name: "Strength"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
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
                amount: 6
            },
            Bonus {
                source: race
                amount: 4
            }
		]
	}

    AbilityScore {
        id: constitution
        name: "Constitution"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 5
            }
        ]
    }

    AbilityScore {
        id: intelligence
        name: "Intelligence"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 1
            }
        ]
    }

    AbilityScore {
        id: wisdom
        name: "Wisdom"
        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: -3
            }
        ]
    }

    AbilityScore {
        id: charisma
        name: "Charisma"
        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: 6
            },
            Bonus {
                source: race
                amount: 2
            }

        ]
    }

    Skill {
        name: "Acrobatics"
        ability: dexterity
    }

    ClassSkill {
        name: "Appraise"
        ability: intelligence
    }

    ClassSkill {
        name: "Bluff"
        ability: charisma
    }

    Skill {
        name: "Climb"
        ability: strength
    }

    Skill {
        name: "Craft"
        ability: intelligence
    }

    Skill {
        name: "Diplomacy"
        ability: charisma
    }

    Skill {
        name: "Disable Device"
        ability: dexterity
    }

//    Skill {

//    }

    Skill {
        name: "Sleight of Hand"
        ability: dexterity
        ranks: 1
    }

    Skill {
        name: "Knowledge (History)"
        ability: intelligence
        ranks: 1
    }

    ClassSkill {
        name: "Knowledge (Planes)"
        ability: intelligence
        ranks: 1
    }

	BonusSource {
		id: pointBuy
        name: "Point Buy"
	}

	BonusSource {
		id: race
        name: "Race (Human)"
	}
}
