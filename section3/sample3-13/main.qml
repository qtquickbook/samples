import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    width: 200
    height: 100

    Text {
        id: text
        text: slider.value
    }
    Slider {
        id: slider
        anchors.top: text.bottom
        from: 0
        to: 100
        value: 100
        stepSize: 1
    }
}
