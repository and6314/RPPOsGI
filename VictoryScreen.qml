import QtQuick 2.0

Item {
    anchors.fill: parent
    visible:false
    height: parent.height
    width:parent.width
    Rectangle{
        x:0
        y:0
        height: parent.height
        width:parent.width

        color : "#0D0E25"
        Image {
            source: "images/flags/hammer.png"
            anchors.centerIn: parent
        }

        Text
        {
            color: "white"
            text: "Победа"
        }
    }

}
