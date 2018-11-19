import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 200
    Grid {
        id: grid
        columns: 2
        Rectangle {width: 50; height: 50; color: "red";}
        Rectangle {width: 50; height: 50; color: "green";}
        Rectangle {width: 50; height: 50; color: "blue";}
        Rectangle {width: 50; height: 50; color: "yellow";}
        Rectangle {width: 50; height: 50; color: "black";}
    }
}
