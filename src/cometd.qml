import QtQuick 1.1

import "cometd.js" as CometdJS

QtObject {
    function initialize() {
        CometdJS.initialize(timerWindow);
        binding.setForwardFunction(CometdJS.forward)
    }
}
