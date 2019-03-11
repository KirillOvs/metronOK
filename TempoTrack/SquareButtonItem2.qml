import QtQuick 2.0

Item {
    id: element
    property alias descriptionText: description.text
    property alias imageSource: btn.imageSource
    property alias mouseArea: btn.mouseArea
    property alias button: btn
    property alias descriptionTextColor: description.color
    property alias borderOpacity: btn.borderOpacity
    property bool val: false

    width: parent.width
    height: 25

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.margins: 5

    SquareButton {
        id: btn
        width: parent.width - 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        borderOpacity: "50";
        mouseArea.onPressed: {
            if(borderOpacity != "00")
                borderOpacity = "99";
        }
        mouseArea.onReleased: {
            if(borderOpacity != "00")
                borderOpacity = "50";
        }

        Text {
            id: description
            text: "text"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            color: "white"
            visible: element.width > 75
        }
    }
}
