import QtQuick 2.3

import "../"
import org.lasath.psychic_bear 1.0

import "../shared/feats" as Feats

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
                amount: 2
            }
        ]
    }

    AbilityScore {
        id: intelligence
        name: "Intelligence"
    }

    AbilityScore {
        id: wisdom
        name: "Wisdom"
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
        ranks: level.value

        modifiers: [
            Bonus {
                source: race
                amount: 4
            }
        ]
    }

    Skill {
        name: "Climb"
        ability: strength
    }

    Skill {
        name: "Craft"
        ability: intelligence
    }

    ClassSkill {
        name: "Diplomacy"
        ability: charisma
        ranks: 2
    }

    Skill {
        name: "Disable Device"
        ability: dexterity
    }

    Skill {
        name: "Disguise"
        ability: dexterity
    }

    Skill {
        name: "Escape Artist"
        ability: dexterity
    }

    Skill {
        name: "Fly"
        ability: charisma
    }

    Skill {
        name: "Handle Animal"
        ability: charisma
    }

    Skill {
        name: "Heal"
        ability: wisdom
    }

    ClassSkill {
        name: "Intimidate"
        ability: charisma
        ranks: 3
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
        }
    }

    Skill {
        name: "Linguistics"
        ability: intelligence
        ranks: 1
    }

    ClassSkill {
        name: "Perception"
        ability: wisdom
        ranks: level.value
    }

    Skill {
        name: "Ride"
        ability: dexterity
    }

    Skill {
        name: "Sense Motive"
        ability: wisdom
    }

    Skill {
        name: "Sleight of Hand"
        ability: dexterity
    }

    Skill {
        name: "Spellcraft"
        ability: intelligence
    }

    Skill {
        name: "Stealth"
        ability: dexterity
        ranks: 1
    }

    Skill {
        name: "Survival"
        ability: wisdom
    }

    Skill {
        name: "Swim"
        ability: strength
    }

    Attribute {
        name: "Unspent Skill Points"
        uri: "attr://skills/totalRanks"

        modifiers: [
            Bonus {
                name: "Elementalist Base Skills"
                amount: 4 * level.value
            },
            Bonus {
                name: "Intelligence Bonus"
                amount: intelligence.permanent.modifier.value
            },
            Bonus {
                name: "Human Favoured Class"
                amount: level.value
            }
        ]
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
                    name: "Level 1 Health Roll (Max)"
                    amount: 8
                },
                Bonus {
                    name: "Level 2 Health Roll (#rage)"
                    amount: 2
                },
                Bonus {
                    name: "Level 3 Health Roll"
                    amount: 6
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

        Attribute {
            name: "Hit Points from Death"
            uri: hp.prefix + "/tillDeath"
            modifiers: [
                Bonus {
                    name: constitution.temporary.name
                    amount: constitution.temporary.value
                },
                Bonus {
                    name: currentHp.name
                    amount: currentHp.value
                }

            ]
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
                name: "Armour (Studded Leather)"
                amount: 3
            },
            Bonus {
                name: "Hawk Badge (Deflection)"
                amount: 1
            },
            Bonus {
                name: "Chain Shirt"
                amount: 4
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
                    name: "Touch Penalty"
                    amount: -acArmourBonus.amount
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
                    name: "Flat Footed Penalty"
                    amount: -acDexBonus.amount
                },
                Bonus {
                    name: "Chain Shirt"
                    amount: 4
                }
            ]
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
                },
                Bonus {
                    source: pointBlankShot
                    amount: 1
                },
                Bonus {
                    source: weaponFocus
                    amount: 1
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

    Item {
        property string prefix: "attr://combat/elementAttack"

        Attribute {
            name: "Elemental Attack Dice"
            uri: parent.prefix + "/dice"

            modifiers: [
                Bonus {
                    name: "Elemental Affrinity"
                    amount: level.value
                }
            ]
        }

        Attribute {
            name: "Elemental Damage Bonus"
            uri: parent.prefix + "/bonus"
            modifiers: [
                Bonus {
                    name: "Force of Will"
                    amount: charisma.temporary.modifier.value
                },
                Bonus {
                    source: pointBlankShot
                    amount: 1
                }
            ]
        }
    }

    Attribute {
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "Elementalist"
            amount: 3
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
        id: pointBlankShot
        uri: "msrc://feats/pointBlankShot"
        name: "Point Blank Shot (Feat)"
        conditional: true
    }

    BonusSource {
        id: weaponFocus
        uri: "msrc://feats/weaponFocus"
        name: "Weapon Focus: Ray (Feat)"
        conditional: true
    }

    BonusSource {
        uri: "msrc://feats/forceOfWill"
        name: "Extra Knacks: Force of Will (Feat)"
        conditional: true
    }

    Feats.Toughness {}
}
