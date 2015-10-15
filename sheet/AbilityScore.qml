import QtQuick 2.3
import org.lasath.psychic_bear 1.0

Item {
	id: root
	property string name

    property string prefix: "attr://abilityScores/" + name.trim().toLowerCase()

	property Attribute temporary: Attribute {
        name: root.name + " (Temp)"
        uri: prefix + "/temporary"

        readOnly: false
		modifiers: [
			Bonus {
				name: "Permanent Value"
				amount: permanent.value
			}
		]

        property Attribute modifier: Attribute {
            name: root.name + " Modifier (Temp)"
            uri: temporary.uri + "/modifier"

            modifiers: [
                Bonus {
                    name: "From Score"
                    amount: Math.floor((root.temporary.value - 10) / 2)
                }
            ]
        }
    }

    property Attribute permanent: Attribute {
        name: root.name
        uri: prefix + "/permanent"

        modifiers: [
            Bonus {
                name: "Default Value"
                amount: 10
            }
        ]

        property Attribute modifier: Attribute {
            name: root.name + " Modifier"
            uri: permanent.uri + "/modifier"

            modifiers: [
                Bonus {
                    name: "From Score"
                    amount: Math.floor((root.permanent.value - 10) / 2)
                }
            ]
        }
    }
}
