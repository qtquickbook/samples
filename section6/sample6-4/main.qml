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
                text: display;
                font.pixelSize: 24
            }
        }
    }
}
