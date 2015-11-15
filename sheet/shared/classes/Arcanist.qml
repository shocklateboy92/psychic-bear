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
        model: _private.spellLevels

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
        }
    }

    Instantiator {
        id: prepList
        model: _private.spellLevels

        Attribute {
            property int spellLevel: modelData
            name: "Prepared Level " + spellLevel + " Spells Per Day"
            uri: "attr://spells/prepared/total/" + spellLevel

            modifiers: [
                Bonus {
                    // TODO: Make function for prepared spells per day table
                    name: "Arcanist Base"
                    amount: 2
                }
            ]
        }
    }

    SpellList {
        id: spellList
        name: "Primary Prepared SpellList, Level 1"
        uri: "spel://spellLists/prepared/default"
        className: "wiz"
        level: 1
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
