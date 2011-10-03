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

    Cometd {
        id: echoService

        property string channel: "/service/echo"

        function echo(message) {
            publish(channel, { msg: message });
        }

        function handleEcho(message) {
            echoText.text = message.data.msg + "\n" + echoText.text;
        }

        Component.onCompleted: {
            setLogLevel("debug");
            configure("http://localhost:8080/cometd");
            handshake();
            subscribe(channel, handleEcho);
        }
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
                echoService.echo(text)
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
