import QtQuick 2.9
import QtQuick.Window 2.2
//import QtQuick.VirtualKeyboard 2.2
import BarModel 1.0
import BeatModel 1.0
import QtQuick.Controls 2.12

Window {
    id: window
    visible: true
    width: 1024
    height: 480
    title: qsTr("TempoTrackDev")

    BarModel {
        id: barModel
    }

    Flickable {
        id: flickable
        contentWidth: window.width
        Row {
            id: row
            height: window.height
            anchors.left: parent.left
            width: window.width

            Rectangle {
                id: controls
                z: 1
                width: 110
                height: window.height
                color: "darkgrey"

                Column {
                    id: column
                    width: 120
                    anchors.fill: parent

                    spacing: 5
                    padding: 5

                    /*Button {
                        width: 60
                        height: 30
                        anchors.margins: 10
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "click"
                        onClicked: barModel.actionClick();
                    }

                    SquareButtonItem2 {
                        id: menu
                        mouseArea.onPressed: {}
                        mouseArea.onReleased: {}
                        mouseArea.onClicked: barModel.select(!val);
                        descriptionText: "";
                        imageSource: "img/lines_icon.svg"
                        borderOpacity: "00"

                    }*/

                    Label  {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Number of bars"
                        font.italic: true
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                    }
                    Frame {
                        id: myControl
                        width: 110
                        height: 80
                        anchors.horizontalCenter: parent.horizontalCenter


                        SquareButton {
                            id: up
                            anchors.left: trackBarsNumber.right
                            anchors.leftMargin: 5
                            anchors.top: trackBarsNumber.top
                            imageSource: "img/plus_icon.svg"
                            borderOpacity: "50"
                            mouseArea.onPressed: { borderOpacity = "99"; }
                            mouseArea.onReleased: { borderOpacity = "50"; }
                            mouseArea.onClicked: { ++trackBarsNumber.currentIndex; }
                        }

                        SquareButton {
                            id: down
                            anchors.left: trackBarsNumber.right
                            anchors.leftMargin: 5
                            anchors.bottom: trackBarsNumber.bottom
                            imageSource: "img/minus_icon.svg"
                            borderOpacity: "50"
                            mouseArea.onPressed: { borderOpacity = "99"; }
                            mouseArea.onReleased: { borderOpacity = "50"; }
                            mouseArea.onClicked: { --trackBarsNumber.currentIndex; }
                        }

                        Tumbler {
                            id: trackBarsNumber
                            width: 65
                            height: 60
                            anchors.left: parent.left
                            anchors.leftMargin: -5
                            wheelEnabled: true
                            currentIndex: 5
                            visibleItemCount: 1
                            font.pixelSize: 40
                            model: {
                                var arr = [];
                                for(var i = 0; i <= 500; ++i)
                                    arr.push(i);
                                return arr;
                            }

                            onCurrentIndexChanged: {
                                /*var num = barModel.count - currentIndex;
                                while(num != 0) {
                                    if(num < 0) {
                                        console.log(num);
                                        barModel.addItem();
                                        ++num;
                                    }
                                    else {
                                        barModel.removeItem();
                                        --num;
                                    }
                                }*/
                            }
                        }


                    }

                    Label  {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Precount"
                        font.italic: true
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                    }

                    Tumbler {
                        id: precountTumbler
                        width: parent.width
                        height: 60
                        wheelEnabled: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        currentIndex: 4; //barModel.preCount();
                        visibleItemCount: 1
                        font.pixelSize: 40
                        model: 40
                        onCurrentIndexChanged: {
                            barModel.preCount(currentIndex);
                        }
                    }

                    Switch {
                        id: locker
                        width: 130
                        text: qsTr("lock")
                        padding: 0
                        anchors.left: parent.left
                        anchors.leftMargin: -10
                        font.pixelSize: 15
                        scale: 0.7
                        onToggled: barModel.lock(checked);
                    }

                    Switch {
                        id: selector
                        width: 130
                        text: qsTr("select")
                        padding: 0
                        anchors.left: parent.left
                        anchors.leftMargin: -10
                        font.pixelSize: 15
                        scale: 0.7
                        onToggled: barModel.select(checked);
                    }

                    /*SquareButtonItem {
                        id: locker
                        mouseArea.onClicked: {
                            barModel.lock(!checked);
                            --precountTumbler.currentIndex;
                        }
                        descriptionText: checked ? "track locked" : "track unlocked";
                        imageSource: checked ? "img/selected_icon.svg" : ""
                    }*/

                    /*SquareButtonItem2 {
                        id: locker
                        mouseArea.onClicked: barModel.lock(!val);
                        descriptionText: val ? "unlock track" : "lock track";
                    }


                    SquareButtonItem2 {
                        id: selector
                        mouseArea.onClicked: {
                            val = val ? false : true;
                            barModel.select(val);
                        }
                        descriptionText: val ? "unselect all" : "select all";
                    }*/

                    SquareButtonItem2 {
                        id: adder
                        mouseArea.onClicked: {
                            if(!barModel.isWorking())
                                barModel.addItem();
                        }
                        descriptionText: val ? "add beat" : "add bar"
                    }

                    SquareButtonItem2 {
                        id: remover
                        mouseArea.onClicked: barModel.removeItem();
                        descriptionText: val ? "remove beat" : "remove bar"
                    }


                    SquareButtonItem2 {
                        id: save
                        mouseArea.onClicked: barModel.removeItem();
                        descriptionText: "save"
                    }
                    SquareButtonItem2 {
                        id: load
                        mouseArea.onClicked: barModel.removeItem();
                        descriptionText: "load"
                    }

                    SquareButtonItem2 {
                        id: update
                        mouseArea.onClicked: barModel.update();
                        descriptionText: "update"
                    }


                }
            }

            ListView {
                id: listView
                orientation: ListView.Horizontal
                width: window.width
                height: window.height
                model: barModel
                property int lowCoordBoundary: 0
                property int highCoorBoundary: 0
                delegate: BarModelDelegate {
                    modelObj: barModel;
                }
            }
        }
    }
}





/*##^## Designer {
    D{i:8;anchors_x:68}D{i:9;anchors_x:"-2"}
}
 ##^##*/
