import QtQuick 2.0

import org.lasath.psychic_bear 1.0
import "."

Item {
    property string prefix: "attr://combat/armourClass"

    Attribute {
        id: acTouch
        name: "Armour Class (Touch)"
        uri: prefix + "/touch"

    }

    Attribute {
        id: acFlatFooted
        name: "Armour Class (Flat-Footed)"
        uri: prefix + "/flatFooted"
    }

    AttributeRef {
        id: acRef
        targetUri: prefix

        onTargetChanged: {
            if (!target) {
                return;
            }

            // TODO: replace with bonus filter
            for (var m in target.modifiers) {
                var mod = target.modifiers[m];
                if (mod.type !== CommonTypes.acDex) {
                    acFlatFooted.addModifier(mod);
                }
                if (mod.type !== CommonTypes.armour) {
                    acTouch.addModifier(mod);
                }
            }
        }
    }
}
