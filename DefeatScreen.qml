import QtQuick 2.0
import QtQuick.Controls 2.0


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
            text: "Поражение"
            font.family: "Helvetica"
            font.pointSize: 18
            x :parent.width / 2 - 60
            y :parent.height /2 - 290
        }
        Text
        {
            color: "white"
            text: "В следующий раз повезет"
            font.family: "Helvetica"
            font.pointSize: 12
            x :parent.width / 2 - 80
            y :parent.height /2 - 260
        }
        MyButton {
            x:parent.width / 2 - 132
            y :parent.height /2 + 260
            Text {

                color: "white"
                font.family: "Helvetica"
                font.pointSize: 12
                text: "Новая игра"
                anchors.centerIn: parent
            }
            onClicked:
            {
                defeatScreen.visible = false
                menuScreen.visible = true
                /*game.newGame()
                gamearea.visible = true
                rightPanel.visible = true
                topPanel.visible = true
                turnButton.visible = true
                map.update()
                rightPanel.update()
                topPanel.update()
                rightPanel.update()*/
            }
        }
    }

}
