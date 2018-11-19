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
                text: day
                font.pixelSize: 24
            }
        }
        section.property: "section"
        section.delegate: sectionDelegate
    }

    ListModel {
        id: weekModel
        ListElement {day: "Sunday";    section: "holiday"}
        ListElement {day: "Monday";    section: "weekday"}
        ListElement {day: "Tuesday";   section: "weekday"}
        ListElement {day: "Wednesday"; section: "weekday"}
        ListElement {day: "Thursday";  section: "weekday"}
        ListElement {day: "Friday";    section: "weekday"}
        ListElement {day: "Saturay";   section: "holiday"}
    }

    Component {
        id: sectionDelegate
        Rectangle {
            width: 300
            height: 24
            color: "lightsteelblue"
            Text {
                text: section
                font.pixelSize: 24
                width: 200
            }
        }
    }
}
