import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Skill {
    modifiers: [
        Bonus {
            name: "Class Skill"
            amount: if(ranks>=1){
                        3
                    }
                    else{
                        0
                    }
        }
    ]
}

