import QtQuick 2.3
import org.lasath.psychic_bear 1.0

import "../"

Item {

    //Attributes
    Attribute {
        id: strength
        name: "Strength"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 4
            }
        ]
    }

    Attribute {
        id: agility
        name: "Agility"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 3
            },
            Bonus {
                name: "Rillian"
                amount: -1
            }
        ]
    }

    Attribute {
        id: toughness
        name: "Toughness"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 6
            }
        ]
    }

    Attribute {
        id: endurance
        name: "Endurance"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 4
            },
            Bonus {
                name: "Rillian"
                amount: -1
            }
        ]
    }

    Attribute {
        id: health
        name: "Health"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 6
            }
        ]
    }

    Attribute {
        id: social
        name: "Social"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 3
            },
            Bonus {
                name: "Rillian"
                amount: 1
            }
        ]
    }

    Attribute {
        id: wits
        name: "Wits"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 5
            },
            Bonus {
                name: "Rillian"
                amount: 1
            }
        ]
    }

    Attribute {
        id: willpower
        name: "Willpower"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 7
            },
            Bonus {
                name: "Rillian"
                amount: 1
            }
        ]
    }

    Attribute {
        id: perception
        name: "Perception"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 4
            }
        ]
    }

    Attribute {
        id: mentalaptitude
        name: "Mental Aptitude"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Initial"
                amount: 5
            }
        ]
    }

    //Derived Sorcery Attributes
    Attribute {
        id: kaa
        name: "Kaa"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((toughness.value + health.value + willpower.value) / 2)
            }

        ]
    }

    Attribute {
        id: form
        name: "Form"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((wits.value + perception.value) / 2)
            }
        ]
    }

    Attribute {
        id: discipline
        name: "Discipline"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((willpower.value + endurance.value) / 2)
            }
        ]
    }

    Attribute {
        id: draw
        name: "Draw"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((strength.value + willpower.value) / 2)
            }
        ]
    }

    Attribute {
        id: art
        name: "Art"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((mentalaptitude.value + endurance.value) / 2)
            }
        ]
    }

    //Derived attributes
    Attribute {
        id: aim
        name: "Aim"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((agility.value + perception.value) / 2)
            }
        ]
    }

    Attribute {
        id: reflex
        name: "Reflex"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((agility.value + wits.value) / 2)
            }
        ]
    }

    Attribute {
        id: move
        name: "Move"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((strength.value + agility.value + endurance.value) / 2)
            }
        ]
    }

    Attribute {
        id: knockout
        name: "Knockout"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor(toughness.value + (willpower.value/2))
            }
        ]
    }

    Attribute {
        id: knockdown
        name: "Knockdown"
        uri: "attr://character/attribute/" + name.trim().toLowerCase()
        modifiers: [
            Bonus {
                name: "Derived"
                amount: Math.floor((strength.value + agility.value) / 2)
            }
        ]
    }


    //Skills
    Skill {
        name: "Carving"
        ranks: 8
        readOnly: false
    }

    Skill {
        name: "Etiquette (Court)"
        ranks: 7
        readOnly: false
    }

    Skill {
        name: "Etiquette (Church)"
        ranks: 7
        readOnly: false
    }

    Skill {
        name: "Meditation"
        ranks: 7
        readOnly: false
    }

    Skill {
        name: "Leadership"
        ranks: 8
        readOnly: false
    }

    Skill {
        name: "Orate"
        ranks: 8
        readOnly: false
    }

    Skill {
        name: "Law"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Read & Write"
        ranks: 7
        readOnly: false
    }

    Skill {
        name: "Theology"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Ancient Languages"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Stewardship"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Diplomacy"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Surgery"
        ranks: 8
        readOnly: false
    }

    Skill {
        name: "Forgery"
        ranks: 10
        readOnly: false
    }

    Skill {
        name: "Sneak"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Arcane Theory"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Ritual Magic"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Symbol Drawing"
        ranks: 7
        readOnly: false
    }

    Skill {
        name: "Herbalist"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Astronomy"
        ranks: 9
        readOnly: false
    }

    Skill {
        name: "Secret Languages"
        ranks: 7
        readOnly: false
    }

    Skill {
        name: "Sailing"
        ranks: 8
        readOnly: false
    }

    Item {
        id: proficiencies
        property string prefix: "attr://combat/proficiencies"

        Attribute {
            id: sculpt
            name: "Sculpt"
            uri: proficiencies.prefix + sculpt.name

            modifiers: [
               Bonus {
                  name: "Base"
                  amount: 2
               }
            ]
        }

        Attribute {
            id: vision
            name: "Vision"
            uri: proficiencies.prefix + vision.name

            modifiers: [
               Bonus {
                  name: "Base"
                  amount: 2
               }
            ]
        }

        Attribute {
            id: profmove
            name: "Move"
            uri: proficiencies.prefix + profmove.name

            modifiers: [
               Bonus {
                  name: "Base"
                  amount: 2
               }
            ]
        }

        Attribute {
            id: glamour
            name: "Glamour"
            uri: proficiencies.prefix + glamour.name

            modifiers: [
               Bonus {
                  name: "Base"
                  amount: 1
               }
            ]
        }
    }


    Item {
        id: hp
        property string prefix: "attr://combat/hitPoints/"

        Attribute {
            name: "Months Aged"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (1)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (2)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (3)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (4)"
            uri: hp.prefix+"/"+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (5)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (6)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (7)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (8)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (9)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (10)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (11)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (12)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (13)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }

        Attribute {
            name: "Damage to (14)"
            uri: hp.prefix+name.trim().toLowerCase()
            readOnly: false
        }
    }

    Item {
        id: saps
        property string prefix: "attr://saps/"

        Attribute {
            name: "Conscience (Heal the Sick)"
            uri: saps.prefix+"healthesick"
            readOnly: false
        }

        Attribute {
            name: "Passion (Magical Surgery)"
            uri: saps.prefix+"magicalsurgery"
            readOnly: false
        }

        Attribute {
            name: "Faith (Dala)"
            uri: saps.prefix+"faith"
            readOnly: false
        }

        Attribute {
            name: "Drive (Clear my name)"
            uri: saps.prefix+"clearmyname"
            readOnly: false
        }

        Attribute {
            name: "Passion (Universal healthcare)"
            uri: saps.prefix+"healthcare"
            readOnly: false
        }

        Attribute {
            name: "Inspiration"
            uri: saps.prefix+"inspiration"
            readOnly: false
        }

        Attribute {
            name: "Drama"
            uri: saps.prefix+"drama"
            readOnly: false
        }
    }

    Item {
        id: pools
        property string prefix: "attr://combat/pools"

        Attribute {
            id: sorcerypool
            name: "Dice from Kaa + Form"
            uri: pools.prefix+"/sorcery"

            modifiers: [
               Bonus {
                  name: "Base pool"
                  amount: kaa.value + form.value
               }
            ]
            readOnly: false
        }

        Attribute {
            id: artpool
            name: "Dice from Art"
            uri: pools.prefix+"/artdice"

            modifiers: [
               Bonus {
                  name: "Base pool"
                  amount: art.value
               }
            ]
            readOnly: false
        }

        Attribute {
            id: disciplinepool
            name: "Dice from Discipline"
            uri: pools.prefix+"/disciplinedice"

            modifiers: [
               Bonus {
                  name: "Base pool"
                  amount: discipline.value
               }
            ]
            readOnly: false
        }

        Attribute {
            id: agingpool
            name: "Aging pool"
            uri: pools.prefix+"/agingdice"
            modifiers: [
                Bonus {
                    name: "Familiar"
                    amount: 1
                }
            ]
            readOnly: false
        }

        Attribute {
            id: sorcerypoolthree
            name: "Spells of Three"
            uri: pools.prefix+"/sorcerythree"

            modifiers: [
               Bonus {
                  name: "Base"
                  amount: sorcerypool.value
               },
               Bonus {
                    name: "Dice from Art"
                    amount:  artpool.value
                }
            ]
        }

        Attribute {
            name: "Spells of Many"
            uri: pools.prefix+"/sorcerymany"

            modifiers: [
               Bonus {
                  name: "Base from Spells of Three"
                  amount: sorcerypoolthree.value
               },
                Bonus {
                    name: "Dice from Discipline"
                    amount: disciplinepool.value
                }
            ]
        }
    }

    Attribute {
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "William"
            amount: 2
        }
    }
}
