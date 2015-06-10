pragma Singleton
import QtQuick 2.0

import org.lasath.psychic_bear 1.0

Item {
    property BonusType armour: BonusType {
        stacking: false
    }

    property BonusType acDex: BonusType {
        stacking: false
    }

    property BonusType sheild: BonusType {
        stacking: false
    }

    property BonusType deflection: BonusType {
        stacking: false
    }
}
