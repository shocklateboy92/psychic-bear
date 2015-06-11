import QtQuick 2.0

import org.lasath.psychic_bear 1.0
import "str_utils.js" as StringUtils

BonusSource {
    conditional: true

    uri: "msrc://spells/" + StringUtils.camelize(name)
}

