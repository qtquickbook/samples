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
import QtQuick.Controls 2.2

RangeSlider {
    id: _slider
    orientation: Qt.Vertical
    background: Rectangle {
        x: (parent.width - width) / 2
        y: _slider.topPadding + _slider.first.handle.height / 2
        width: 4
        height: _slider.availableHeight - _slider.first.handle.height
        color: "gray"

        Rectangle {
            y: (_slider.second.visualPosition) * parent.height
            height: _slider.first.visualPosition  * parent.height - y
            width: parent.width
            gradient: Gradient {
                  GradientStop { position: 0.0; color: "#ff0000" }
                  GradientStop { position: 0.25; color: "#ffff00" }
                  GradientStop { position: 0.5; color: "#00ffff" }
                  GradientStop { position: 0.75; color: "#0000ff" }
                  GradientStop { position: 1.0; color: "#000000" }
            }
        }
    }
}
