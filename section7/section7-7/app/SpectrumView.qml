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

Flickable {
    id: flick

    property alias source: image.source

    contentWidth: Math.max(width, height)
    contentHeight: Math.max(width, height)

    clip: true

    ScrollBar.vertical: ScrollBar { }
    ScrollBar.horizontal: ScrollBar { }

    PinchArea {
        id: pincharea

        width: Math.max(flick.contentWidth, flick.width)
        height: Math.max(flick.contentHeight, flick.height)

        property real initialWidth
        property real initialHeight

        onPinchStarted: {
            initialWidth = flick.contentWidth
            initialHeight = flick.contentHeight
        }

        onPinchUpdated: {
            flick.contentX +=
                    pinch.previousCenter.x - pinch.center.x
            flick.contentY +=
                    pinch.previousCenter.y - pinch.center.y

            var estimateWidth =
                    initialWidth * pinch.scale;
            var estimateHeight =
                    initialHeight * pinch.scale;

            if (estimateWidth < flick.width) {
                estimateWidth = flick.width;
                estimateHeight =
                flick.width * initialHeight / initialWidth;
            }

            flick.resizeContent(estimateWidth,
                              estimateHeight, pinch.center)
        }

        onPinchFinished: {
            flick.returnToBounds()
        }

        Item {
            id: subarea
            width: flick.contentWidth
            height: flick.contentHeight
            Spectrum {
                id: image
                scale: implicitWidth === 0 ? 1 : parent.width / image.implicitWidth
                transformOrigin: Item.TopLeft
            }
        }
    }
}
