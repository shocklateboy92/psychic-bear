import QtQuick 2.3

import "qrc:/sheet"
import org.lasath.psychic_bear 1.0

Item {

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
                    amount: 6
                },
                Bonus {
                    name: "Level 2 Health Roll (#rage)"
                    amount: 5
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
            id: nonLethal
            name: "Non-Lethal Hit Point Damage"
            uri: hp.prefix + "/nonLethal"

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
                },
                Bonus {
                    name: nonLethal.name
                    amount: nonLethal.value
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
                name: "Dexterity"
                amount: dexterity.temporary.modifier.value
                type: CommonTypes.acDex
            }
        ]
    }

    ArmourClassHelper {
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

}

