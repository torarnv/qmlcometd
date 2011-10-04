/**************************************************************************
**
**  Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
**  All rights reserved.
**
**  Contact: Nokia Corporation (qt-info@nokia.com)
**
**  You may use this file under the terms of the BSD license as follows:
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are
**  met:
**
**    * Redistributions of source code must retain the above copyright
**      notice, this list of conditions and the following disclaimer.
**
**    * Redistributions in binary form must reproduce the above copyright
**      notice, this list of conditions and the following disclaimer in
**      the documentation and/or other materials provided with the
**      distribution.
**
**    * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**      the names of its contributors may be used to endorse or promote
**      products derived from this software without specific prior written
**      permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
**  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
**  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
**  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
**  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
**  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
**  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
**  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

import QtQuick 1.1

import "private"

Item {
    id: api

    property string url
    property string logLevel
    property int maxConnections
    property int backoffIncrement
    property int maxBackoff
    property bool reverseIncomingExtensions
    property int maxNetworkDelay
    property variant requestHeaders
    property bool appendMessageTypeToURL
    property bool autoBatch

    onUrlChanged: pimpl.setConfigurationProperty()
    onLogLevelChanged: pimpl.setConfigurationProperty()
    onMaxConnectionsChanged: pimpl.setConfigurationProperty()
    onBackoffIncrementChanged: pimpl.setConfigurationProperty()
    onMaxBackoffChanged: pimpl.setConfigurationProperty()
    onReverseIncomingExtensionsChanged: pimpl.setConfigurationProperty()
    onMaxNetworkDelayChanged: pimpl.setConfigurationProperty()
    onRequestHeadersChanged: pimpl.setConfigurationProperty()
    onAppendMessageTypeToURLChanged: pimpl.setConfigurationProperty()
    onAutoBatchChanged: pimpl.setConfigurationProperty()

    property bool connected: false

    // Public API, matching the API from Cometd.js

    function configure() {
        pimpl.call();
        pimpl.updateConfiguration();
    }

    function init() {
        pimpl.call();
        pimpl.updateConfiguration();
    }

    function setLogLevel() {
        pimpl.call();
        pimpl.updateConfiguration();
    }

    function registerTransport() { return pimpl.call(); }
    function getTransportTypes() { return pimpl.call(); }
    function unregisterTransport() { return pimpl.call(); }
    function findTransport() { return pimpl.call(); }
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

        Component.onCompleted: {
            updateConfiguration()
            addListener('/meta/connect', updateConnectionStatus);
            addListener('/meta/disconnect', updateConnectionStatus);
        }

        function updateConnectionStatus() {
            api.connected = !isDisconnected();
        }

        function call() {
            var caller = arguments.callee.caller;
            return forward(caller.name, caller.arguments);
        }

        property bool updatingConfiguration: false

        // Update the Cometd config based on the declarative property change
        function setConfigurationProperty() {
            if (updatingConfiguration)
                return

            var signalName = arguments.callee.caller.name
            var propertyName = /^on(.+?)Changed$/.exec(signalName)[1]
            propertyName = propertyName.charAt(0).toLowerCase() + propertyName.substr(1)

            var config = {}
            config[propertyName] = api[propertyName]
            api.configure(config)
        }

        // Update the declarative properties based on the Cometd configuration
        function updateConfiguration() {
            updatingConfiguration = true
            var config = getConfiguration()
            for (var prop in config) {
                if (prop == "advice")
                    continue

                api[prop] = config[prop]
            }
            updatingConfiguration = false
        }
    }
}
