import QtQuick 2.3

import "../"
import org.lasath.psychic_bear 1.0

Item {
	AbilityScore {
		id: strength
		name: "Strength"

		permanent.modifiers: [
			Bonus {
				source: pointBuy
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
                amount: 4
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
                amount: 2
            }
        ]
    }

    AbilityScore {
        id: charisma
        name: "Charisma"

    }

    ClassSkill {
        name: "Acrobatics"
        ability: dexterity
        ranks: 1
    }

    ClassSkill {
        name: "Appraise"
        ability: intelligence
        ranks: 1
    }

    ClassSkill {
        name: "Bluff"
        ability: charisma
        ranks: 1

        modifiers: [
            Bonus {
                source: race
                amount: 4
            }
        ]
    }

    ClassSkill {
        name: "Climb"
        ability: strength
    }

    ClassSkill {
        name: "Craft"
        ability: intelligence
    }

    ClassSkill {
        name: "Diplomacy"
        ability: charisma
    }

    ClassSkill {
        name: "Disable Device"
        ability: dexterity
        ranks: level.value
    }

    ClassSkill {
        name: "Disguise"
        ability: dexterity
        ranks: level.value
    }

    ClassSkill {
        name: "Escape Artist"
        ability: dexterity
    }

    ClassSkill {
        name: "Fly"
        ability: dexterity
        ranks: 1
    }

    ClassSkill {
        name: "Handle Animal"
        ability: charisma
    }

    ClassSkill {
        name: "Heal"
        ability: wisdom
        ranks: 1
    }

    ClassSkill {
        name: "Intimidate"
        ability: charisma
    }


    ClassSkill {
        name: "Knowledge Arcana"
        ability: intelligence
        ranks: 1
    }


    ClassSkill {
        name: "Knowledge Engineering"
        ability: intelligence
    }

    ClassSkill {
        name: "Knowledge Dungeoneering"
        ability: intelligence
        ranks: 1
    }

    ClassSkill {
        name: "Knowledge Geography"
        ability: intelligence
    }

    ClassSkill {
        name: "Knowledge History"
        ability: intelligence
    }

    ClassSkill {
        name: "Knowledge Local"
        ability: intelligence
        ranks: level.value
    }

    ClassSkill {
        name: "Knowledge Nature"
        ability: intelligence
    }

    ClassSkill {
        name: "Knowledge Nobility"
        ability: intelligence
        ranks: level.value
    }

    ClassSkill {
        name: "Knowledge Religion"
        ability: intelligence
    }

    ClassSkill {
        name: "Knowledge Planes"
        ability: intelligence
    }

    ClassSkill {
        name: "Linguistics"
        ability: intelligence
    }

    ClassSkill {
        name: "Perception"
        ability: wisdom
        ranks: level.value
    }

    ClassSkill {
        name: "Ride"
        ability: dexterity
    }

    ClassSkill {
        name: "Sense Motive"
        ability: wisdom
    }

    ClassSkill {
        name: "Sleight of Hand"
        ability: dexterity
        ranks: level.value
    }

    ClassSkill {
        name: "Spellcraft"
        ability: intelligence
        ranks: level.value
    }

    ClassSkill {
        name: "Stealth"
        ability: dexterity
        ranks: level.value

        modifiers: [
            Bonus{
                name: "fiddlesticks"
                amount: 4
            }
        ]
    }

    ClassSkill {
        name: "Survival"
        ability: wisdom
    }

    ClassSkill {
        name: "Swim"
        ability: strength
    }


    ClassSkill {
        name: "Use Magic Device"
        ability: charisma
        ranks: 1
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
                    amount: constitution.temporary.modifier.value*level.value
                },
                Bonus {
                    name: "Level 1 Health Roll (Max)"
                    amount: 8
                },
                Bonus {
                    name: "Favoured Class"
                    amount: level.value
                },
                Bonus {
                    source: toughness
                    amount: Math.max(3, level.value)
                },
                Bonus{
                 name: "Level 2 Health Roll"
                 amount: 5
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
        id: armourClass
        name: "Armour Class"
        uri: "attr://combat/armourClass"

        modifiers: [
            Bonus {
                name: "Base"
                amount: 10
            },
            Bonus {
                id: acDexBonus
                name: "Dexterity"
                amount: dexterity.temporary.modifier.value
            },
            Bonus {
                id: acArmourBonus
                name: "Armour (Mage Armor)"
                amount: 4
            },
            Bonus {
                id: acShieldBonus
                name: "Buckler"
                amount: 1
            },
            Bonus {
                id: acDeflectionBonus
                name: "Hawk Badge"
                amount: 1
            }

        ]

        Attribute {
            name: "Armour Class (Touch)"
            uri: parent.uri + "/touch"

            modifiers: [
                Bonus {
                    name: "Normal Armour Class"
                    amount: armourClass.value
                },
                Bonus {
                    name: "no armor"
                    amount: -acArmourBonus.amount
                },
                Bonus {
                    name: "no shield"
                    amount: -acShieldBonus.amount
                }
            ]
        }

        Attribute {
            name: "Armour Class (Flat-Footed)"
            uri: parent.uri + "/flatFooted"

            modifiers: [
                Bonus {
                    name: "Normal Armour Class"
                    amount: armourClass.value
                },
                Bonus {
                    name: "no dex"
                    amount: -acDexBonus.amount
                }
            ]
        }
    }

    Attribute {
        name: "Initiative"
        modifiers: [
            Bonus {
                name: dexterity.temporary.modifier.name
                amount: dexterity.temporary.modifier.value
            }
        ]
    }

    SavingThrow {
        name: "Fortitude"
        ability: constitution
    }
    SavingThrow {
        name: "Reflex"
        ability: dexterity
    }
    SavingThrow {
        name: "Will"
        ability: wisdom
        primary: true
    }

    Attribute {
        name: "Base Attack Bonus"
        uri: "attr://combat/baseAttackBonus"
        modifiers: [
            Bonus {
                name: "Base Attack Bonus"
                amount: Math.floor((level.value * 3) / 4)
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
                    name: dexterity.temporary.modifier.name
                    amount: dexterity.temporary.modifier.value
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

        Attribute{
            name: "Ranged Attack Damage"
            uri: parent.uri + "/rangedDamage"
            modifiers: [
                Bonus{
                    name: "Weapon Damage in d8's"
                    amount:1
                },
                Bonus {
                    name: strength.temporary.modifier.name
                    amount: strength.temporary.modifier.value
                }
            ]
        }

        Attribute{
            name: "melee Attack Damage"
            uri: parent.uri + "/meleeDamage"
            modifiers: [
                Bonus{
                    name: "Weapon Damage in d6's"
                    amount:1
                },
                Bonus {
                    name: strength.temporary.modifier.name
                    amount: strength.temporary.modifier.value
                }
            ]
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
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "Sneak"
            amount: 2
        }
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
        id: toughness
        name: "Toughness (Feat)"
    }

    BonusSource {
        id: pointBlankShot
        name: "Point Blank Shot (Feat)"
    }

    BonusSource {
        id: weaponFocus
        name: "Weapon Focus: Ray (Feat)"
    }
}
