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
                amount: 8
            }
        ]
    }

    AbilityScore {
        id: dexterity
        name: "Dexterity"

        permanent.modifiers: [
            Bonus {
                amount: 6
            }
        ]
    }

    AbilityScore {
        id: constitution
        name: "Constitution"

        permanent.modifiers: [
            Bonus {
                amount: 9
            }
        ]
    }

    AbilityScore {
        id: intelligence
        name: "Intelligence"

        permanent.modifiers: [
            Bonus {
                amount: 2
            }
        ]
    }

    AbilityScore {
        id: wisdom
        name: "Wisdom"
        permanent.modifiers: [
            Bonus {
                amount: 2
            }
        ]
    }

    AbilityScore {
        id: charisma
        name: "Charisma"
    }

    Skill {
        name: "Acrobatics"
        ability: dexterity
        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -acPenalty.value
            }
        ]
    }

    Skill {
        name: "Appraise"
        ability: intelligence
    }

    Skill {
        name: "Bluff"
        ability: charisma
    }

    ClassSkill {
        name: "Climb"
        ability: strength
        ranks: level.value
        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -acPenalty.value
            }
        ]
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
        ranks: 1
    }

    Skill {
        name: "Disguise"
        ability: dexterity
    }

    Skill {
        name: "Escape Artist"
        ability: dexterity
        ranks: 2
        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -acPenalty.value
            }
        ]
    }

    Skill {
        name: "Fly"
        ability: dexterity
        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -acPenalty.value
            }
        ]
    }

    Skill {
        name: "Handle Animal"
        ability: charisma
    }

    Skill {
        name: "Heal"
        ability: wisdom
        ranks: level.value
    }

    ClassSkill {
        name: "Intimidate"
        ability: charisma
        ranks: level.value
        modifiers: [
            Bonus {
                name: "Intimidating Prowress"
                amount: strength.temporary.modifier.value
            }

        ]
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
            "Planes",
            "Religion"
        ]

        Skill {
            name: "Knowledge (" + modelData + ")"
            ability: intelligence
        }
    }

    ClassSkill {
        name: "Knowledge (Nobility)"
        ability: intelligence
        ranks: level.value
    }

    Skill {
        name: "Linguistics"
        ability: intelligence
    }

    ClassSkill {
        name: "Perception"
        ability: wisdom
        ranks: level.value
    }

    Skill {
        name: "Ride"
        ability: dexterity
        ranks: 1
    }

    Skill {
        name: "Sense Motive"
        ability: wisdom
    }

    Skill {
        name: "Sleight of Hand"
        ability: dexterity
        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -acPenalty.value
            }
        ]
    }

    Skill {
        name: "Spellcraft"
        ability: intelligence
    }

    Skill {
        name: "Stealth"
        ability: dexterity
        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -acPenalty.value
            }
        ]
    }

    Skill {
        name: "Survival"
        ability: wisdom
    }

    ClassSkill {
        name: "Swim"
        ability: strength
        ranks: 2

        modifiers: [
            Bonus {
                name: acPenalty.name
                amount: -(acPenalty.value*2)
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
                    amount: 12
                },
                Bonus {
                    name: "Level 2 Health Roll"
                    amount: 8
                },
                Bonus {
                    name: "Level 3 Health Roll"
                    amount: 7
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
        id: acPenalty
        name: "Armour Penalty"
        uri: "attr://combat/armourPenalty"
        modifiers: [
            Bonus {
                source: weararmour
                name: weararmour.name
                amount: 4
            }
        ]
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
                name: "Hawk Badge (Deflection)"
                amount: 1
            },
            Bonus {
                id: acArmourBonus
                source: weararmour
                name: weararmour.name
                amount: 6
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
                },
                Bonus {
                    source: weararmour
                    name: weararmour.name
                    amount: 6
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
                    source: weararmour
                    name: weararmour.name
                    amount: 6
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
        primary: true
    }
    SavingThrow {
        name: "Reflex"
        ability: dexterity
        primary: true
    }
    SavingThrow {
        name: "Will"
        ability: wisdom
    }

    Attribute {
        name: "Base Attack Bonus"
        uri: "attr://combat/baseAttackBonus"
        modifiers: [
            Bonus {
                name: "Base Attack Bonus"
                amount: level.value
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
                },
                Bonus {
                    source: pamasterweapon
                    name: pamasterweapon.name
                    amount: 2
                },
                Bonus {
                    source: pabarraniweapon
                    name: pabarraniweapon.name
                    amount: 1
                },
                Bonus {
                    source: masterofbody
                    name: masterofbody.name
                    amount: constitution.temporary.modifier.value
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
            name: "Weapon master"
            amount: 3
        }
    }

    BonusSource {
        id: pamasterweapon
        uri: "msrc://feats/masterofweapons"
        name: "Master of weapons (Polearm)"
        conditional: true
    }

    BonusSource {
        id: pabarraniweapon
        uri: "msrc://feats/barranicrafts"
        name: "Barrani Craftsmen (Polearm +1)"
        conditional: true
    }

    BonusSource {
        id: masterofbody
        uri: "msrc://feats/masterofbody"
        name: "Master of body"
        conditional: true
    }

    BonusSource {
        id: weararmour
        uri: "msrc://body/weararmour"
        name: "Wear armour (Agile Breastplate)"
        conditional: true
    }
    Feats.Toughness {}
}
