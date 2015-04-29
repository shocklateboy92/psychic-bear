import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Item {
    property string prefix: "attr://combat/carryCapacity/"
    property variant table: [
        [  0,   0,   0],
        [  3,   6,  10],
        [  6,  13,  20],
        [ 10,  20,  30],
        [ 13,  26,  40],
        [ 16,  33,  50],
        [ 20,  40,  60],
        [ 23,  46,  70],
        [ 26,  53,  80],
        [ 30,  60,  90],
        [ 33,  66, 100],
        [ 38,  76, 115],
        [ 43,  86, 130],
        [ 50, 100, 150],
        [ 58, 116, 175],
        [ 66, 133, 200],
        [ 76, 153, 230],
        [ 86, 173, 260],
        [100, 200, 300],
        [116, 233, 350],
        [133, 266, 400],
        [153, 306, 460],
        [173, 346, 520],
        [200, 400, 600],
        [233, 466, 700],
        [266, 533, 800],
        [306, 613, 920],
        [346, 693, 1040],
        [400, 800, 1200],
        [466, 933, 1400]
    ]

    Attribute {
        name: "Light Load"
        uri: prefix + "/light"
        modifiers: [
            Bonus {
                name: "Base"
                amount: (table[strength.temporary.value])[0]
            }
        ]
    }

    Attribute {
        name: "Medium Load"
        uri: prefix + "/medium"
        modifiers: [
            Bonus {
                name: "Base"
                amount: (table[strength.temporary.value])[1]
            }
        ]
    }

    Attribute {
        name: "Heavy Load"
        uri: prefix + "/heavy"
        modifiers: [
            Bonus {
                name: "Base"
                amount: (table[strength.temporary.value])[2]
            }
        ]
    }
}

