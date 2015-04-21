import QtQuick 2.3
import org.lasath.psychic_bear 1.0

Item {
	id: root
	property string name

    property string prefix: "attr://abilityScores/" + name.trim().toLowerCase()

	property Attribute permanent: Attribute {
        name: root.name
        uri: prefix + "/permanent"

        modifiers: [
            Bonus {
                name: "Default Value"
                amount: 10
            }
        ]

        Attribute {
            name: root.name + " Modifier"
            uri: parent.uri + "/modifier"

            modifiers: [
                Bonus {
                    name: "From Score"
                    amount: Math.floor((root.permanent.value - 10) / 2)
                }
            ]
        }
	}

	property Attribute temporary: Attribute {
        name: root.name + " (Temp)"
        property int mod: Math.floor((value - 10) / 2)

		modifiers: [
			Bonus {
				name: "Permanent Value"
				amount: permanent.value
			}
		]

        Attribute {
            name: root.name + " Modifier (Temp)"
            uri: parent.uri + "/modifier"

            modifiers: [
                Bonus {
                    name: "From Score"
                    amount: Math.floor((root.temporary.value - 10) / 2)
                }
            ]
        }
    }
}
