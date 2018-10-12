import QtQuick 2.0

Rectangle {
    id: mybutton
    signal clicked
    color: "#191D4A" //"#000033"
    height: 64
    width: 264
    border {
        color: "grey"
        width: 2
    }


    MouseArea {
            anchors.fill: parent
            onClicked: mybutton.clicked()
            onPressed: mybutton.color = "#000033"
            onReleased: mybutton.color = "#191D4A"
        }
}
