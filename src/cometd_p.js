.pragma library

function typeOf(obj) {
    var str = Object.prototype.toString.call(obj);
    return str.match(/\s(.+?)\]/)[1].toLowerCase();
}

// Set up cometd namespace
var org = org || {};
org.cometd = {};

// And a fake window object
var window = {}
window.location = {}
window.location.host = ""

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

function handle(caller) {
    _instance[caller.name].apply(_instance, caller.arguments);
}
