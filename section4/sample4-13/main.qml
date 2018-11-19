import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 200
    height: 200
    GridLayout {
        id: grid
        columns: 2
        anchors.fill: parent
        Rectangle {Layout.fillWidth: true; Layout.fillHeight: true; color: "red";}
        Rectangle {Layout.fillWidth: true; Layout.fillHeight: true; color: "green";}
        Rectangle {Layout.fillWidth: true; Layout.fillHeight: true; color: "blue";}
        Rectangle {Layout.fillWidth: true; Layout.fillHeight: true; color: "yellow";}
        Rectangle {Layout.fillWidth: true; Layout.fillHeight: true; color: "black";}
    }
}
