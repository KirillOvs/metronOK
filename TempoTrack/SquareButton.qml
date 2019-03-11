import QtQuick 2.0

Rectangle {
    property alias imageSource: image.source
    property alias mouseArea: mArea

    property string borderOpacity: "99"
    width: 25
    height: 25
    color: "#00000000"
    radius: 5
    border.color: "#" + borderOpacity + "ffffff";

    Image {
        id: image
        width: 23
        height: 23
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        scale: 0.8
    }
    MouseArea {
        id: mArea
        anchors.fill: parent
    }
}
