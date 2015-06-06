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
            },
            Bonus {
                name: size.name
                amount: Math.pow(2, size.value)
            }
        ]
    }

    Skills {

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
            },
            Bonus {
                name: size.name
                amount: -Math.pow(2, size.value)
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
                },
                Bonus{
                    name: "Level 3 Health Roll"
                    amount: 7
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
            },

            Bonus {
                name: size.name
                amount: -Math.pow(2, size.value)/2
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
    Attribute {
        name: "Size"
        id: size
        uri: "attr://combat/Size"
        property var sizeNames: {"-4":"Fine",
                                 "-3":"Diminutive",
                                 "-2":"Tiny",
                                 "-1":"Small",
                                 0:"Medium",
                                 1:"Large",
                                 2:"Huge",
                                 3:"Gargantuan",
                                 4:"Colossal"}
        modifiers: [
            Bonus {
                name: size.sizeNames[size.value]
                amount: 0
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
                },
                Bonus {
                    name: size.name
                    amount: -Math.pow(2, size.value)/2
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
                    name: size.name
                    amount: -Math.pow(2, size.value)/2
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
                },
                Bonus {
                    name: size.name
                    amount: Math.pow(2, size.value)/2
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
                },
                Bonus {
                    name: size.name
                    amount: Math.pow(2, size.value)/2
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
        id: toughness
        name: "Toughness (Feat)"
    }
    Spell {
        id: alterSelf
        name: "Alter self (gain dex)"
        effects: [
            Bonus {
                target: dexterity.temporary
                amount: 2
            },
            Bonus {
                target: size
                amount: -1
            }

        ]
    }

}
