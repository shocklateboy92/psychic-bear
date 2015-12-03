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
            },
            Bonus {
                id: l4dingPoint
                name: "Level4 dingPoint"
                amount: 1
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
        ranks: 1
    }

    Skill {
        name: "Disguise"
        ability: charisma
        ranks: 0
    }

    ClassSkill {
        name: "Escape Artist"
        ability: dexterity
        ranks: 2
    }

    ClassSkill {
        name: "Fly"
        ability: dexterity
        ranks: level.value
    }

    Skill {
        name: "Handle Animal"
        ability: charisma
        ranks: 0
    }

    ClassSkill {
        name: "Heal"
        ability: wisdom
        ranks: level.value
    }

    Skill {
        name: "Intimidate"
        ability: charisma
        ranks: 0
    }

    Skill {
        name: "Knowledge (Arcana)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Dungeoneering)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Engineering)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Geography)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (History)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Local)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Nature)"
        ability: intelligence
        ranks: 0
    }

    ClassSkill {
        name: "Knowledge (Navigation)"
        ability: intelligence
        ranks: 1
    }

    Skill {
        name: "Knowledge (Nobility)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Planes)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Knowledge (Religion)"
        ability: intelligence
        ranks: 0
    }

    Skill {
        name: "Linguistics"
        ability: intelligence
        ranks: 0
    }

    ClassSkill {
        name: "Perception"
        ability: wisdom
        ranks: level.value
    }

    Skill {
        name: "Perform: Testimony"
        ability: charisma
        ranks: 3
    }

    ClassSkill {
        name: "Profession: Chess"
        ability: intelligence
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
        ranks: 1
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
        ranks: 2
    }

    ClassSkill {
        name: "Survival"
        ability: wisdom
        ranks: 1
    }

    Skill {
        name: "Swim"
        ability: strength
        ranks: 0
    }

    Skill {
        name: "Use Magic Device"
        ability: intelligence
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
                    amount: constitution.temporary.modifier.value * level.value
                },
                Bonus {
                    source: toughness
                    amount: level.value < 3 ? 3 : level.value;
                },
                Bonus {
                    name: "Level 1 Health Roll (Max)"
                    amount: 10
                },
                Bonus {
                    name: "Level 2 Health Roll"
                    amount: 6
                },
                Bonus {
                    name: "Level 3 Health Roll"
                    amount: 10
                },
                Bonus {
                    name: "Level 4 Health Roll"
                    amount: 6
                },
                Bonus {
                    name: "Level 5 Health Roll"
                    amount: 8
                },
                Bonus {
                    name: "Favoured Class (All Levels)"
                    amount: level.value
                }

            ]
        }

        Attribute {
            id: currentHp
            name: "Current Hit Points"
            uri: hp.prefix + "/current"

            modifiers: [
                Bonus {
                    name: "Initial Value (Max)"
                    amount: maxHp.value
                }
            ]
            readOnly: false
        }
    }

    Attribute {
        name: "Initiative"
        uri: "attr://combat/initiative"
        modifiers: [
            Bonus {
                name: dexterity.temporary.modifier.name
                amount: dexterity.temporary.modifier.value
            }
        ]
    }

    Attribute {
        name: "Spell Resistance"
        uri: "attr://combat/spellResistance"
    }

    Attribute {
        name: "Base Attack Bonus"
        uri: "attr://combat/baseAttackBonus"
        modifiers: [
            Bonus {
                name: "Base Attack Bonus"
                amount: Math.floor((level.value * 4) / 4)
                id: baseAttackBonus
            }
        ]


        Attribute {
            name: "Melee Attack Bonus"
            uri: parent.uri + "/melee"
            modifiers: [
                Bonus {
                    name: baseAttackBonus.name
                    amount: baseAttackBonus.amount
                },
                Bonus {
                    name: strength.temporary.modifier.name
                    amount: strength.temporary.modifier.value
                }
            ]
        }

        Attribute {
            name: "Ranged Attack Bonus"
            uri: parent.uri + "/ranged"
            modifiers: [
                Bonus {
                    name: baseAttackBonus.name
                    amount: baseAttackBonus.amount
                },
                Bonus {
                    name: dexterity.temporary.modifier.name
                    amount: dexterity.temporary.modifier.value
                }
            ]
        }

        Attribute {
            name: "Point Blank Shot (30ft radius)"
            uri: parent.uri + "/ranged"
            modifiers: [
                Bonus {
                    name: baseAttackBonus.name
                    amount: baseAttackBonus.amount
                },
                Bonus {
                    name: dexterity.temporary.modifier.name
                    amount: dexterity.temporary.modifier.value
                },
                Bonus {
                     name: "Point Blank Shot"
                     amount: 1
                }
            ]
        }

        Attribute {
            name: "Ranged Damage Bonus"
            uri: parent.uri + "/ranged"
            modifiers: [
                Bonus {
                    name: dexterity.temporary.modifier.name
                    amount: dexterity.temporary.modifier.value
                }
            ]
        }

        Attribute {
            name: "Point Blank Shot Damage Bonus"
            uri: parent.uri + "/ranged"
            modifiers: [
                Bonus {
                    name: dexterity.temporary.modifier.name
                    amount: dexterity.temporary.modifier.value
                },
                Bonus {
                     name: "Point Blank Shot"
                     amount: 1
                }
            ]
        }

        BonusSource {
            id: pointBlankShot
            name: "Point-Blank Shot (Combat)"
            conditional: false
            //description: "Benefit: You get a +1 bonus on attack and damage rolls with ranged weapons at ranges of up to 30 feet."
            //rangeInFeet: 30
            //range:
        }

        Attribute {
            name: "Combat Maneuver Bonus (CMB)"
            uri: parent.uri + "/CMB"
            modifiers: [
                Bonus {
                    name: baseAttackBonus.name
                    amount: baseAttackBonus.amount
                },
                Bonus {
                    name: strength.temporary.modifier.name
                    amount: strength.temporary.modifier.value
                }
            ]
        }

        Attribute {
            name: "Combat Maneuver Defense (CMD)"
            uri: parent.uri + "/CMD"
            modifiers: [
                Bonus {
                    name: baseAttackBonus.name
                    amount: baseAttackBonus.amount
                },
                Bonus {
                    name: "Base CMB"
                    amount: 10
                },
                Bonus {
                    name: strength.temporary.modifier.name
                    amount: strength.temporary.modifier.value
                },
                Bonus {
                    name: dexterity.temporary.modifier.name
                    amount: dexterity.temporary.modifier.value
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
                source: armourBonus
                amount: 4
                id: acArmour
            },
            Bonus {
                name: "Shield"
                amount: 0
                id: acShield
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
                source: deflectionBonus
                amount: 1
                id: acDeflect
            }
        ]

        Attribute {
            name: "Armour Class (Touch)"
            uri: parent.uri + "/touch"
            modifiers: [
                acBase,
                acDexterity,
                acSize,
                acDeflect
            ]
        }

        Attribute {
            name: "Armour Class (Flat-Footed)"
            uri: parent.uri + "/flatFooted"
            modifiers: [
                acBase,
                acArmour,
                acShield,
                acSize,
                acNatural,
                acDeflect
            ]
        }
    }

    CarryCapacity {

    }

    Attribute {
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "Weapon Specialist"
            amount: 5
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
        name: "Will"
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

    BonusSource {
        id: toughness
        uri: "msrc://feats/toughness"
        name: "Toughness (Feat)"
        conditional: true
    }

    BonusSource {
        id: armourBonus
        name: "Mithral Shirt"
        conditional: true
    }

    BonusSource {
        id: deflectionBonus
        name: "Hawk Badge"
        conditional: true
    }

    BonusSource {
        id: skillfulFlyer
        name: "Skillful Flyer"
        conditional: false
        //description: "At 4th level, the specialist improves his/her fly speed to 60ft/good and at 8th level this becomes 70ft/perfect"
    }
}
