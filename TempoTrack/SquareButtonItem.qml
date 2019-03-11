import QtQuick 2.0

Item {
    id: element
    property alias descriptionText: description.text
    property alias imageSource: btn.imageSource
    property alias mouseArea: btn.mouseArea
    property alias button: btn
    property alias descriptionTextColor: description.color
    property alias descriptionReadOnly: description.readOnly
    property alias borderOpacity: btn.borderOpacity
    property alias markerTextItem: description
    property bool checked: false

    width: parent.width
    height: 25

    //border.color: "red"
    //anchors.horizontalCenter: parent.horizontalCenter
    anchors.left: parent.left
    anchors.margins: 5

    SquareButton {
        id: btn
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }
    TextEdit {
        id: description
        text: "text"
        anchors.verticalCenter: btn.verticalCenter
        anchors.left: btn.right
        anchors.leftMargin: 3
        color: "white"
        readOnly: true
        visible: element.width > 75
        selectionColor: "black"
        onFocusChanged: {
            if(readOnly)
                return;
            if(focus)
                selectAll();
            else
                model.markerText = text; // ???
        }
    }
}
