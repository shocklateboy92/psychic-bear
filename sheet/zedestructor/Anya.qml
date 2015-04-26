import QtQuick 2.3
import org.lasath.psychic_bear 1.0

import "../"

Item {
	AbilityScore {
		id: strength
		name: "Strength"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
                amount: 3
            },
            Bonus {
                source: race
                amount: -2
            }
		]
	}

	AbilityScore {
        id: dexterity
        name: "Dexterity"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
                amount: 7
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
                amount: 6
            },
            Bonus {
                source: race
                amount: -2
            }
        ]
    }

    AbilityScore {
        id: intelligence
        name: "Intelligence"

        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: -3
            },
            Bonus {
                source: race
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
                amount: 6
            },
            Bonus {
                source: race
                amount: -2
            }
        ]
    }

    AbilityScore {
        id: charisma
        name: "Charisma"
        permanent.modifiers: [
            Bonus {
                source: pointBuy
                amount: -3
            },
            Bonus {
                source: race
                amount: 2
            }

        ]
    }

    ClassSkill {
        name: "Acrobatics"
        ability: dexterity
        ranks: 1
    }

    Skill {
        name: "Appraise"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Bluff"
        ability: charisma
        ranks: 0
    }

    Skill {
        name: "Climb"
        ability: strength
        ranks: 0
    }

    Skill {
        name: "Craft"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Diplomacy"
        ability: charisma
        ranks: 0
    }

    ClassSkill {
        name: "Disable Device"
        ability: dexterity
        ranks: 0
    }

    Skill {
        name: "Disguise"
        ability: dexterity
        ranks: 0
    }

    ClassSkill {
        name: "Escape Artist"
        ability: dexterity
        ranks: 1
    }

    ClassSkill {
        name: "Fly"
        ability: charisma
        ranks: 1
    }

    Skill {
        name: "Handle Animal"
        ability: charisma
        ranks: 0
    }

    ClassSkill {
        name: "Heal"
        ability: wisdom
        ranks: 1
    }

    Skill {
        name: "Intimidate"
        ability: charisma
        ranks: 0
    }

    Repeater {
        model: [
            "Arcana",
            "Dungeoneering",
            "Engineering",
            "Geography",
            "History",
            "Local",
            "Nature",
            "Nobility",
            "Planes",
            "Religion"
        ]

        Skill {
            name: "Knowledge (" + modelData + ")"
            ability: intelligence
            ranks: 0
        }
    }

    Skill {
        name: "Linguistics"
        ability: intelligence
        ranks: 0
    }

    ClassSkill {
        name: "Perception"
        ability: wisdom
        ranks: 1
    }

    ClassSkill {
        name: "Ride"
        ability: dexterity
        ranks: 0
    }

    Skill {
        name: "Sense Motive"
        ability: wisdom
        ranks: 0
    }

    ClassSkill {
        name: "Sleight of Hand"
        ability: dexterity
        ranks: 1
    }

    Skill {
        name: "Spellcraft"
        ability: intelligence
        ranks: 0
    }

    ClassSkill {
        name: "Stealth"
        ability: dexterity
        ranks: 0
    }

    ClassSkill {
        name: "Survival"
        ability: wisdom
        ranks: 0
    }

    Skill {
        name: "Swim"
        ability: strength
        ranks: 0
    }

    Skill {
        name: "Use Magic Device"
        ability: strength
        ranks: 0
    }

    Item {
        id: hp
        property string prefix: "attr://combat/hitPoints"

        Attribute {
            id: maxHp
            name: "Maximum Hit Points"
            uri: hp.prefix + "/maximum"

            modifiers: [
                Bonus {
                    name: constitution.temporary.modifier.name
                    amount: constitution.temporary.modifier.value
                },
                Bonus {
                    name: "Toughness"
                    amount: level.value < 3 ? 3 : level.value;
                },
                Bonus {
                    name: "Level 1 Health Roll (Max)"
                    amount: 10
                }

            ]
        }

        Attribute {
            name: "Current Hit Points"
            uri: hp.prefix + "/current"

            modifiers: [
                Bonus {
                    name: "Initial Value (Max)"
                    amount: maxHp.value
                }

            ]
        }
    }

    Attribute {
        name: "Armour Class"
        uri: "attr://combat/armourClass"

        modifiers: [
            Bonus {
                name: "Base AC"
                amount: 10
                id: acBase
            },
            Bonus {
                name: "Armour"
                amount: 2
                id: acArmour
            },
            Bonus {
                name: "Shield"
                amount: 0
                id: acShield
            },
            Bonus {
                name: "Other"
                amount: 0
                id: acOther
            },
            Bonus {
                name: dexterity.temporary.modifier.name
                amount: dexterity.temporary.modifier.value
                id: acDexterity
            },
            Bonus {
                name: "Size"
                amount: 0
                id: acSize
            },
            Bonus {
                name: "Natural"
                amount: 0
                id: acNatural
            },
            Bonus {
                name: "Deflect"
                amount: 0
                id: acDeflect
            },
            Bonus {
                name: "Misc"
                amount: 0
                id: acMisc
            }
        ]

        Attribute {
            name: "Armour Class (Touch)"
            uri: parent.uri + "/touch"
            modifiers: [
                acBase,
                acDexterity
            ]
        }

        Attribute {
            name: "Armour Class (Flat-Footed)"
            uri: parent.uri + "/flatFooted"
            modifiers: [
                acBase,
                acArmour
            ]
        }
    }

    Attribute {
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "Weapon Specialist"
            amount: 1
        }
    }

    SavingThrow {
        name: "Fortitude"
        ability: constitution
        primary: false
    }

    SavingThrow {
        name: "Reflex"
        ability: dexterity
        primary: true
    }

    SavingThrow {
        name: "Willpower"
        ability: wisdom
        primary: true
    }

	BonusSource {
		id: pointBuy
        name: "Point Buy"
	}

	BonusSource {
		id: race
        name: "Race (Aerian)"
	}
}
