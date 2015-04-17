Item {
	id: root
	property string name

	property Attribute permanent: Attribute {
		name: root.name + " Permanent Value"
		property int mod: Math.floor((value - 10) / 2)
	}

	property Attribute temporary: Attribute {
		name: root.name + " Temporary Value"
		property int mod: Math.floor((value - 10) / 2)

		modifiers: [
			Bonus {
				name: "Permanent Value"
				amount: permanent.value
			}
		]
	}
}