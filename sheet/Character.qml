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
        id: dexterity
		name: "Intelligence"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
				amount: 1
            },
            Bonus {
                source: race
                amount: 4
            }
		]
	}

	BonusSource {
		id: pointBuy
	}

	BonusSource {
		id: race
	}
}
