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


    Instantiator {
        // FIXME: re-enable once a resource-manager has been built that
        //        can handle objects being destroyed
//        model: Math.max(Math.floor(levelRef.target.value / 2), 1) + 1
        model: 2

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
                id: remainingSpells
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
            Attribute {
                id: saveDC
                name: "Level %1 Spell Save DC".arg(spellLevel)
                uri: "attr://spells/savingThrow/" + spellLevel

                modifiers: [
                    Bonus {
                        name: "Base"
                        amount: 10
                    },
                    Bonus {
                        name: "Spell Level"
                        amount: spellLevel
                    },
                    Bonus {
                        name: intTempRef.target.name
                        amount: intTempRef.target.value
                    },
                    Bonus {
                        source: potentMagic
                        amount: 2
                    }
                ]
            }

            SpellList {

                name: "Prepared Spells, Level %1".arg(spellLevel)
                uri: "spel://spellLists/prepared/default/%1".arg(spellLevel)

                className: "wiz"
                level: spellLevel

                totalCasts: totalSpells
                remainingCasts: remainingSpells
                saveDc: saveDC
            }
            SpellList {

                name: "Known Spells, Level %1".arg(spellLevel)
                uri: "spel://spellLists/known/" + spellLevel

                className: "wiz"
                level: spellLevel

                totalCasts: totalSpells
                remainingCasts: remainingSpells
                saveDc: saveDC
            }
        }
    }


    BonusSource {
        id: potentMagic

        name: "Potent Magic (Arcanist Exploit)"
        uri: "msrc://classFeatures/arcanist/exploits/potentMagic"

        conditional: true
        active: false
    }


    AttributeRef {
        id: levelRef
        targetUri: "attr://level"
    }
    AttributeRef {
        id: intRef
        targetUri: "attr://abilityScores/intelligence/permanent/modifier"
    }
    AttributeRef {
        id: intTempRef
        targetUri: "attr://abilityScores/intelligence/temporary/modifier"
    }
}
