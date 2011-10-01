import QtQuick 1.1

import "private"

Item {
    // Public API, matching the API from Cometd.js
    function registerTransport() { return pimpl.call(); }
    function getTransportTypes() { return pimpl.call(); }
    function unregisterTransport() { return pimpl.call(); }
    function findTransport() { return pimpl.call(); }
    function configure() { return pimpl.call(); }
    function init() { return pimpl.call(); }
    function handshake() { return pimpl.call(); }
    function disconnect() { return pimpl.call(); }
    function startBatch() { return pimpl.call(); }
    function endBatch() { return pimpl.call(); }
    function batch() { return pimpl.call(); }
    function addListener() { return pimpl.call(); }
    function removeListener() { return pimpl.call(); }
    function clearListeners() { return pimpl.call(); }
    function subscribe() { return pimpl.call(); }
    function unsubscribe() { return pimpl.call(); }
    function clearSubscriptions() { return pimpl.call(); }
    function publish() { return pimpl.call(); }
    function getStatus() { return pimpl.call(); }
    function isDisconnected() { return pimpl.call(); }
    function setBackoffIncrement() { return pimpl.call(); }
    function getBackoffIncrement() { return pimpl.call(); }
    function getBackoffPeriod() { return pimpl.call(); }
    function setLogLevel() { return pimpl.call(); }
    function registerExtension() { return pimpl.call(); }
    function unregisterExtension() { return pimpl.call(); }
    function getExtension() { return pimpl.call(); }
    function getName() { return pimpl.call(); }
    function getClientId() { return pimpl.call(); }
    function getURL() { return pimpl.call(); }
    function getTransport() { return pimpl.call(); }
    function getConfiguration() { return pimpl.call(); }
    function getAdvice() { return pimpl.call(); }

    Cometd {
        id: pimpl

        function call() {
            var caller = arguments.callee.caller;
            return forward(caller.name, caller.arguments);
        }
    }
}
