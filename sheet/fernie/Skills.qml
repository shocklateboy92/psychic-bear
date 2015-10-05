import QtQuick 2.3

import "../"
import org.lasath.psychic_bear 1.0

Item {
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
    }

    Skill {
        name: "Climb"
        ability: strength
        ranks: 1
    }

    Skill {
        name: "Craft"
        ability: intelligence
    }

    ClassSkill {
        name: "Diplomacy"
        ability: charisma
    }

    Skill {
        name: "Disable Device"
        ability: dexterity
    }

    Skill {
        name: "Disguise"
        ability: charisma
    }

    ClassSkill {
        name: "Elementalist Sight"
        ability: wisdom
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
    }

    Instantiator {
        model: [
            "Arcana",
            "Dungeoneering",
            "Engineering",
            "Geography",
            "History",
            "Local",
            "Nobility",
            "Planes",
            "Religion"
        ]

        Skill {
            name: "Knowledge (" + modelData + ")"
            ability: intelligence
            ranks: 1
        }
    }

    ClassSkill {
        name: "Knowledge (Nature)"
        ability: intelligence
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
                name: "Arcanist Base Skills"
                amount: 2 * level.value
            },
            Bonus {
                name: "Intelligence Bonus"
                amount: intelligence.permanent.modifier.value * level.value
            },
            Bonus {
                name: "Human Favoured Class"
                amount: level.value
            }
        ]
    }


}

