import QtQuick 2.3

import org.lasath.psychic_bear 1.0

Item {
    function getSpellsPerDayOf(spellLevel, casterLevel) {
        if (spellLevel === 1) {
            casterLevel += 1;
        }

        if (Math.floor(casterLevel / 2) >= spellLevel) {
            return Math.min(casterLevel - (spellLevel * 2) + 2, 4);
        }

        return 0;
    }

    function getBonusSpellsPerDayOf(spellLevel, abilityModifier) {
        return Math.max(Math.ceil((abilityModifier - spellLevel + 1) / 4), 0);
    }


    QtObject {
        id: _private
        property variant spellLevels: [1,2,3,4,5,6,7,8,9]
    }

    Instantiator {
        model: 3

        Item {
            property int spellLevel: modelData

            Attribute {
                id: totalSpells
                name: "Total Level " + spellLevel + " Spells Per Day"
                uri: "attr://spells/castsPerDay/total/" + spellLevel

                modifiers: [
                    Bonus {
                        name: "Arcanist Base"
                        amount: getSpellsPerDayOf(spellLevel, levelRef.target.value)
                    },
                    Bonus {
                        name: "Bonus Spells (INT)"
                        amount: getBonusSpellsPerDayOf(spellLevel, intRef.target.value)
                    }
                ]
            }

            Attribute {
                name: "Remaining Level " + spellLevel + " Spells Per Day"
                uri: "attr://spells/castsPerDay/remaining/" + spellLevel
                readOnly: false

                modifiers: [
                    Bonus {
                        name: "Total Spells"
                        amount: totalSpells.value
                    }
                ]
            }

            SpellList {
                name: "Prepared Spells, Level %1".arg(spellLevel)
                uri: "spel://spellLists/prepared/default/%1".arg(spellLevel)

                className: "wiz"
                level: spellLevel
            }
        }
    }


    AttributeRef {
        id: levelRef
        targetUri: "attr://level"
    }
    AttributeRef {
        id: intRef
        targetUri: "attr://abilityScores/intelligence/permanent/modifier"
    }
}
