import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 300
    height: 300

    ListView {
        id: weekView
        anchors.fill: parent
        model: weekModel
        delegate: Component {
            id: weekDelegate
            Text {
                text: modelData
                font.pixelSize: 24
            }
        }
    }

    ListModel {
        id: weekModel
        ListElement {day: "Sunday"}
        ListElement {day: "Monday"}
        ListElement {day: "Tuesday"}
        ListElement {day: "Wednesday"}
        ListElement {day: "Thursday"}
        ListElement {day: "Friday"}
        ListElement {day: "Saturay"}
    }
}
