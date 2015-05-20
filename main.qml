import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {

    width: 800
    height: 600

    GLRenderer {
    }
    Rectangle {
        color: Qt.rgba(1, 1, 1, 0.5)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -50
    }

    Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "HELLO SYMMETRY"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 100
    }
}
