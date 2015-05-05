import QtQuick 2.0
import org.lasath.psychic_bear 1.0
import ".."

item{

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
}
