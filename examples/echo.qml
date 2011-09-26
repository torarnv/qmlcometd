import QtQuick 1.1
import Cometd 1.0

/*
 * Run 'mvn clean install -DskipTests=true' from src/3rdparty/cometd
 * and then 'cd cometd-demo && mvn jetty:run' to start the Cometd
 * demo application. Point your browser to http://localhost:8080
 * to verify that the server is running.
 *
 * Then run this example, type some text, and press enter to have
 * the echo service of the server send the text back to you.
 */

Rectangle {
    id: app

    property string echoService: "/service/echo"

    function echo(message) {
        cometd.publish(echoService, { msg: message });
    }

    function handleEcho(message) {
        echoText.text = message.data.msg + "\n" + echoText.text;
    }

    Component.onCompleted: {
        cometd.setLogLevel("debug");
        cometd.configure("http://localhost:8080/cometd");
        cometd.handshake();
        cometd.subscribe(echoService, handleEcho);
    }

    width: 500; height: 500
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#ccc" }
        GradientStop { position: 1.0; color: "#ddd" }
    }

    Rectangle {
        id: inputBox
        border.color: "gray"
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#dfd" }
            GradientStop { position: 1.0; color: "#efe" }
        }

        height: 24

        TextInput {
            id: textInput
            focus: true
            anchors {
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: 1
                left: parent.left; right: parent.right
                margins: 5
            }
            font.pixelSize: 14
            text: "Hello from Cometd!"

            Keys.onReturnPressed: {
                app.echo(text)
            }
        }
    }

    Rectangle {
        border.color: "gray"
        anchors {
            top: inputBox.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            margins: 10
        }

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ddf" }
            GradientStop { position: 1.0; color: "#eef" }
        }

        Flickable {
            id: echoFlickable
            contentHeight: echoText.height
            clip: true

            anchors {
                fill: parent
                margins: 5
            }

            Text {
                id: echoText
                font.pixelSize: 14
            }
        }
    }
}
