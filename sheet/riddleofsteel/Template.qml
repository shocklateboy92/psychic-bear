import QtQuick 2.3
import org.lasath.psychic_bear 1.0

import "../"

Item {
    //Attributes
    Attribute {
		id: strength
		name: "Strength"
	}

    Attribute {
        id: agility
        name: "Agility"
	}

    Attribute {
        id: toughness
        name: "Toughness"
    }

    Attribute {
        id: endurance
        name: "Endurance"
    }

    Attribute {
        id: health
        name: "Health"
    }

    Attribute {
        id: social
        name: "Social"
    }

    Attribute {
        id: wits
        name: "Wits"
    }

    Attribute {
        id: willpower
        name: "Willpower"
    }

    Attribute {
        id: perception
        name: "Perception"
    }

    Attribute {
        id: mentalaptitude
        name: "Mental Aptitude"
    }

    //Derived Sorcery Attributes
    Attribute {
        id: kaa
        name: "Kaa"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (toughness.temporary.value + health.temporary.value + willpower.temporary.value) / 2
            }

        ]
    }

    Attribute {
        id: form
        name: "Form"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (wits.temporary.value + perception.temporary.value) / 2
            }
        ]
    }

    Attribute {
        id: dicipline
        name: "Discipline"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (willpower.temporary.value + endurance.temporary.value) / 2
            }
        ]
    }

    Attribute {
        id: draw
        name: "Draw"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (strength.temporary.value + willpower.temporary.value) / 2
            }
        ]
    }

    Attribute {
        id: art
        name: "Art"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (mentalaptitude.temporary.value + endurance.temporary.value) / 2
            }
        ]
    }

    //Derived attributes
    Attribute {
        id: aim
        name: "Aim"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (agility.temporary.value + perception.temporary.value) / 2
            }
        ]
    }

    Attribute {
        id: reflex
        name: "Reflex"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (agility.temporary.value + wits.temporary.value) / 2
            }
        ]
    }

    Attribute {
        id: move
        name: "Move"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (strength.temporary.value + agility.temporary.value + endurance.temporary.value) / 2
            }
        ]
    }

    Attribute {
        id: knockout
        name: "Knockout"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: toughness.temporary.value + (willpower.temporary.value/2)
            }
        ]
    }

    Attribute {
        id: knockdown
        name: "Knockdown"
        modifiers: [
            Bonus {
                name: "Derived"
                amount: (strength.temporary.value + agility.temporary.value) / 2
            }
        ]
    }


    //Insert skills based off of your skill packs

    /*
    Skill {
        name: "DERP"
        ability: intelligence
        ranks: 0
    }
    */

    Item {
        id: proficiencies
        property string prefix: "attr://combat/proficiencies"

        /*
         * Add your proficiencies
        Attribute {
            id: sculpt
            name: "Sculpt"
            uri: proficiencies.prefix + "/sculpt"

            modifiers: [
               Bonus {
                  name: "Constant"
                  amount: 3
               }
            ]
        }
        */
    }


    Item {
        id: hp
        property string prefix: "attr://combat/hitPoints"

        Repeater {
            model: [ "i", "ii", "iii", "iv", "v", "vi",
                   "vii", "viii", "ix", "x", "xi", "xii", "xiii", "xiv"]

            Attribute {
                name: "Damage to ("+modelData+")"
                uri: hp.prefix+"/"+modelData

                modifiers: [
                    Bonus {
                        name: "Base damage"
                        amount: 0
                    }
                ]
            }
        }
    }

    Item {
        id: pools
        property string prefix: "attr://combat/pools"

        /*
        Attribute {
            name: "Missile"
            uri: pools.prefix+"/missile"

            modifiers: [
               Bonus {
                  name: "Base pool"
                  amount: 13
               }
            ]
        }
        */
    }

    CarryCapacity {

    }

    Attribute {
        id: level
        name: "Character Level"
        uri: "attr://level"

        modifiers: Bonus {
            name: "YOUR CHARACTER NAME"
            amount: 1
        }
    }
}
