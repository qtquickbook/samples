/**
 * Copyright (c) 2018 Nobumasa Murakami
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480

    ListView {
        id: deviceListView
        anchors.fill: parent
        model: devices
        highlightMoveDuration: 0
        interactive: currentIndex === -1
        delegate: listnode
        currentIndex: -1
    }
    Component {
        id: listnode
        ColumnLayout {
            id: deviceRect
            property bool isCurrentItem: ListView.isCurrentItem
            width: parent.width
            height: ListView.isCurrentItem ? deviceListView.height : deviceListView.height / 5
            spacing: 0
            clip: true
            Title {
                Layout.fillWidth: true
                Layout.preferredHeight: deviceRect.isCurrentItem ? 40 : deviceListView.height / 5
                text: name
                level: inputlevel
                checked: active
                onCheckedChanged:
                    active = checked
                onClicked: {
                    if (deviceRect.isCurrentItem) {
                        deviceListView.currentIndex = -1
                    } else {
                        deviceListView.currentIndex = index
                    }
                }
                Behavior on Layout.preferredHeight {
                    NumberAnimation {
                        easing.type: Easing.OutQuad
                    }
                }
            }
            PanelLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                source: imagePath
                rate: sampleRate
            }
            Behavior on height {
                NumberAnimation {
                    easing.type: Easing.OutQuad
                }
            }
        }
    }
}

