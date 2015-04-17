Item {
	AbilityScore {
		id: strength
		name: "Strength"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
				amount: -3
			},
			Bonus {
				source: race
				amount: 4
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
		id: intelligence
		name: "Intelligence"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
				amount: 1
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