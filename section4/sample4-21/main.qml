import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 200
    height: 200

    Component.onCompleted: {
        var component = Qt.createComponent("CustomItem.qml");
        component.createObject(window, {"anchors.fill": window});
    }
}
