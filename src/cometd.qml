import QtQuick 1.1

import "cometd_p.js" as Pimpl

QtObject {
    id: cometd

    function forwardToImplementation() {
        return Pimpl.handle(arguments.callee.caller);
    }

    // Public API, matching the API from Cometd.js
    function registerTransport() { return forwardToImplementation(); }
    function getTransportTypes() { return forwardToImplementation(); }
    function unregisterTransport() { return forwardToImplementation(); }
    function findTransport() { return forwardToImplementation(); }
    function configure() { return forwardToImplementation(); }
    function init() { return forwardToImplementation(); }
    function handshake() { return forwardToImplementation(); }
    function disconnect() { return forwardToImplementation(); }
    function startBatch() { return forwardToImplementation(); }
    function endBatch() { return forwardToImplementation(); }
    function batch() { return forwardToImplementation(); }
    function addListener() { return forwardToImplementation(); }
    function removeListener() { return forwardToImplementation(); }
    function clearListeners() { return forwardToImplementation(); }
    function subscribe() { return forwardToImplementation(); }
    function unsubscribe() { return forwardToImplementation(); }
    function clearSubscriptions() { return forwardToImplementation(); }
    function publish() { return forwardToImplementation(); }
    function getStatus() { return forwardToImplementation(); }
    function isDisconnected() { return forwardToImplementation(); }
    function setBackoffIncrement() { return forwardToImplementation(); }
    function getBackoffIncrement() { return forwardToImplementation(); }
    function getBackoffPeriod() { return forwardToImplementation(); }
    function setLogLevel() { return forwardToImplementation(); }
    function registerExtension() { return forwardToImplementation(); }
    function unregisterExtension() { return forwardToImplementation(); }
    function getExtension() { return forwardToImplementation(); }
    function getName() { return forwardToImplementation(); }
    function getClientId() { return forwardToImplementation(); }
    function getURL() { return forwardToImplementation(); }
    function getTransport() { return forwardToImplementation(); }
    function getConfiguration() { return forwardToImplementation(); }
    function getAdvice() { return forwardToImplementation(); }

    Component.onCompleted: {
        Pimpl.initialize(timerWindow);
    }
}
