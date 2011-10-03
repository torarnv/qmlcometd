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

// Set up cometd namespace
var org = org || {};
org.cometd = {};

// Add fake window object
var window = {}
window.location = {}
window.location.host = ""

function typeOf(obj) {
    var str = Object.prototype.toString.call(obj);
    return str.match(/\s(.+?)\]/)[1].toLowerCase();
}

// Redirect logging to QML
window.console = {
    output : function(arguments) {
        var out = [];
        for (var i = 0; i < arguments.length; ++i) {
            var str = JSON.stringify(arguments[i]);
            if (typeOf(arguments[i]) === "string")
                str = str.replace(/^"|"$/g, "");
            out.push(str);
        }
        console.log(out.join(" "));
    },

    'warn' : function() { this.output(arguments) },
    'info' : function() { this.output(arguments) },
    'debug' : function() { this.output(arguments) }
}

function LongPollingTransport() {
    var _super = new org.cometd.LongPollingTransport();
    var that = org.cometd.Transport.derive(_super);

    // QML's XMLHttpRequest does not enforce the same origin policy,
    // so pretend that we always support cross-domain requests.
    that.accept = function(version, crossDomain, url) {
        return _super.accept(version, false, url);
    };

    that.xhrSend = function(packet) {

        if (packet.sync) {
            packet.onError("error", "Sync mode not supported by QML");
            return;
        }

        var request = new XMLHttpRequest();

        packet.headers["Content-Type"] = "application/json;charset=UTF-8";

        request.onreadystatechange = function() {
            if (request.readyState == XMLHttpRequest.DONE) {
                if (request.status != 200) {
                    packet.onError("error", "Unexpected status: " + request.status);
                    return;
                }

                var response = request.responseText;
                if (response === null || response.length <= 0) {
                    packet.onError("error", "Missing or empty response text");
                    return;
                }

                packet.onSuccess(response);
            }
        }

        request.open("POST", packet.url, packet.sync !== true);

        for (var header in packet.headers)
            request.setRequestHeader(header, packet.headers[header]);

        request.send(packet.body);

        return request;
    };

    return that;
}

var _instance = undefined;

function initialize(timerWindow) {

    window.setTimeout = timerWindow.setTimeout
    window.clearTimeout = timerWindow.clearTimeout

    Qt.include("cometd/Cometd.js")
    Qt.include("cometd/Utils.js")
    Qt.include("cometd/TransportRegistry.js")
    Qt.include("cometd/Transport.js")
    Qt.include("cometd/RequestTransport.js")
    Qt.include("cometd/LongPollingTransport.js")
    Qt.include("cometd/cometd-json.js")

    org.cometd.JSON.toJSON = JSON.stringify;
    org.cometd.JSON.fromJSON = JSON.parse;

    _instance = new org.cometd.Cometd;
    _instance.registerTransport('long-polling', new LongPollingTransport());
}

function forward(name, args) {
    return _instance[name].apply(_instance, args);
}
