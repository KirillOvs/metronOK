import QtQuick 2.0
import BeatModel 1.0
import BarModel 1.0

Rectangle {
    id: viewDelegate

    //anchors.verticalCenter: parent.verticalCenter
    property BarModel modelObj: null
    property BeatModel beatModel: null;

    onModelObjChanged: {
        beatModel = modelObj.getBeatModel(model.index);
    }


    height: parent.height// - 20
    width: model.size * 20

    //border.width: 2;
    border.color: model.selected ? "red" : "#00000000"
    color: model.index & 1 ? "darkgrey" : "grey";

    Marker {
        visible: model.marked;
    }

    Column {
        width: parent.width;
        anchors.top: parent.top;
        anchors.left: parent.left;
        spacing: 5;

        SquareButtonItem {
            id: marker
            mouseArea.onClicked: {
                model.marked = model.marked ? false : true;
                if(model.marked) {
                    markerTextItem.forceActiveFocus();
                    markerTextItem.selectAll();
                }
            }
            descriptionText: model.markerText;
            descriptionTextColor: model.marked ? "green" : "white";
            imageSource: model.marked ? "img/selected_icon.svg" : "";
            opacity: model.marked ? 1 : 0.5;
            descriptionReadOnly: !model.marked;
        }

        SquareButtonItem {
            id: select
            visible: viewDelegate.width
            mouseArea.onClicked: model.selected = model.selected ? false : true;
            descriptionText: model.selected ? "selected" : "unselected";
            imageSource: model.selected ? "img/selected_icon.svg" : ""
            opacity: model.selected ? 1 : 0.5;
        }

        SquareButtonItem {
            id: lock
            visible: viewDelegate.width
            mouseArea.onClicked: model.locked = model.locked ? false : true;
            descriptionText: model.locked ? "locked" : "unlocked";
            imageSource: model.locked ? "img/selected_icon.svg" : ""
            opacity: model.locked ? 1 : 0.5;
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.left: parent.left
            //anchors.leftMargin: 5
            renderType: Text.NativeRendering
            text: model.index - model.preCountNum >= 0 ? model.index - model.preCountNum + 1 : "-"
            color: "#20ffffff"
            font.pixelSize: 40
        }

        Text {
            id: barProperty
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.left: parent.left
            //anchors.leftMargin: 5
            renderType: Text.NativeRendering
            text: model.size + "/" + model.dimension
            color: "#20ffffff"
            font.pixelSize: 20
        }
    }

    // nested model of beats
    Row {
        height: parent.height
        ListView {
            orientation: ListView.Horizontal
            width: viewDelegate.width
            model: viewDelegate.beatModel
            delegate: BeatModelDelegate {}
        }
    }
    MouseArea { anchors.fill: parent; z: -1; onClicked: { viewDelegate.forceActiveFocus(); } onPressAndHold: {console.log("hold"); }}
}
