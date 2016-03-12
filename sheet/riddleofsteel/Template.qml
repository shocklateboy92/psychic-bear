import QtQuick 2.3
import org.lasath.psychic_bear 1.0

import "../"

Item {
    //Attributes
	AbilityScore {
		id: strength
		name: "Strength"
	}

	AbilityScore {
        id: agility
        name: "Agility"
	}

    AbilityScore {
        id: toughness
        name: "Toughness"
    }

    AbilityScore {
        id: endurance
        name: "Endurance"
    }

    AbilityScore {
        id: health
        name: "Health"
    }

    AbilityScore {
        id: social
        name: "Social"
    }

    AbilityScore {
        id: wits
        name: "Wits"
    }

    AbilityScore {
        id: willpower
        name: "Willpower"
    }

    AbilityScore {
        id: perception
        name: "Perception"
    }

    AbilityScore {
        id: mentalaptitude
        name: "Mental Aptitude"
    }

    //Derived Sorcery Attributes
    AbilityScore {
        id: kaa
        name: "Kaa"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (toughness.temporary.value + health.temporary.value + willpower.temporary.value) / 2
            }

        ]
    }

    AbilityScore {
        id: form
        name: "Form"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (wits.temporary.value + perception.temporary.value) / 2
            }
        ]
    }

    AbilityScore {
        id: dicipline
        name: "Discipline"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (willpower.temporary.value + endurance.temporary.value) / 2
            }
        ]
    }

    AbilityScore {
        id: draw
        name: "Draw"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (strength.temporary.value + willpower.temporary.value) / 2
            }
        ]
    }

    AbilityScore {
        id: art
        name: "Art"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (mentalaptitude.temporary.value + endurance.temporary.value) / 2
            }
        ]
    }

    //Derived attributes
    AbilityScore {
        id: aim
        name: "Aim"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (agility.temporary.value + perception.temporary.value) / 2
            }
        ]
    }

    AbilityScore {
        id: reflex
        name: "Reflex"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (agility.temporary.value + wits.temporary.value) / 2
            }
        ]
    }

    AbilityScore {
        id: move
        name: "Move"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: (strength.temporary.value + agility.temporary.value + endurance.temporary.value) / 2
            }
        ]
    }

    AbilityScore {
        id: knockout
        name: "Knockout"
        permanent.modifiers: [
            Bonus {
                name: "Derived"
                amount: toughness.temporary.value + (willpower.temporary.value/2)
            }
        ]
    }

    AbilityScore {
        id: knockdown
        name: "Knockdown"
        permanent.modifiers: [
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
