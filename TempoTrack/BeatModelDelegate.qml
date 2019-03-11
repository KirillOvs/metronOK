import QtQuick 2.0

Item {
    height: parent.height
    width: 20;    

    Rectangle {
        id: tempoAnchor
        anchors.left: parent.left

        y: model.y;
        width: 20
        height: 20
        radius: width * .5
        color: model.isActive ? "red" : "lightgrey"
        border {
            color: "lightgreen"
            width: 1
        }

        Text {
            anchors.centerIn: parent
            renderType: Text.NativeRendering
            text: model.index+1
        }

        TempoTip {
            id: tempoTip
            height: 20
            width:  20
            tipText: model.tempo
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent

            onPressed: {
                if(model.isOwnerBarLocked) return;
                tempoTip.visible = true;
                tempoAnchor.border.color = "green";
                // colorAnimation ?
            }
            onPressAndHold: {
                model.currentBeat = model.index;
            }

            onReleased: {
                //if(viewDelegate.modelObj.isTrackLocked()) {
                tempoTip.visible = false;
                tempoAnchor.border.color = "lightgreen";
                // colorAnimation ?

                if(model.tempo >= 240) {
                    model.y = listView.highCoorBoundary + 15;
                    model.tempo = (viewDelegate.height - tempoAnchor.y) * .5;
                }

                if(model.tempo <= 20) {
                    model.y = listView.lowCoordBoundary - 15;
                    model.tempo = (viewDelegate.height - tempoAnchor.y) * .5;
                }
            }

            onDoubleClicked: {
                console.log("!");
            }

            onMouseYChanged: {
                if(model.tempo >= 240) { // 250
                    model.tempo = 240;
                    if(listView.highCoorBoundary === 0)
                        listView.highCoorBoundary = tempoAnchor.y;
                    return;
                }

                if(model.tempo <= 20) {
                    model.tempo = 20;
                    if(listView.lowCoordBoundary === 0)
                        listView.lowCoordBoundary = tempoAnchor.y;
                    return;
                }
                model.y = tempoAnchor.y + mouseY;
                model.tempo = (viewDelegate.height - (tempoAnchor.y + mouseY)) * .5;
            }
        }
    }
}

