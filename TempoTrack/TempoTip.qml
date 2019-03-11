import QtQuick 2.0

Rectangle {
    property alias tipText: text.text
    anchors.top: parent.bottom
    anchors.topMargin: 5
    anchors.horizontalCenter: parent.horizontalCenter
    color: "#80666666"
    radius: 5
    visible: false
    Text {
        id: text
        anchors.centerIn: parent
        renderType: Text.NativeRendering
        text: model.tempo
        color: "white"
    }
}
