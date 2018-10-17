import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import backend 1.0
import map 1.0
import recruitment 1.0
import toppanel 1.0
import rightpanel 1.0
import game 1.0

ApplicationWindow {
    id: root
    width: 1400
    height: 800
    visible: true
    color: "#000033"
    Game {
        id: game
        m: map
        Component.onCompleted:
        {
            newGame()
            gamearea.visible = true
            maparea.contentWidth  = (map.sizeX+1) * 64
            maparea.contentHeight = (map.sizeY+1) * 64
        }
    }

    MyButton {
        id : turnButton
        onClicked:
        {
            map.newturn()
            topPanel.update()
            rightPanel.update()
        }
        x : 1050
        y:650
        width:rightPanel.width
        Text {

            color: "white"
            font.family: "Helvetica"
            font.pointSize: 12
            text: "Конец хода"
            anchors.centerIn: parent
        }

    }
    TopPanel {
        id:topPanel
        x:5
        y:5
        height: 30
        width : gamearea.width
        m:map

    }
    RightPanel {
        id: rightPanel
        x :1050
        y:5
        width : 300
        height: 600
        m:map
    }

    Rectangle
    {
        id : gamearea
        visible: false
        x:5
        y:35
        border {
            color: "red"
            width: 4
        }
        width: 64*15+14
        height: 64*11+14
        Flickable {
            id: maparea
            width: gamearea.width
            height: gamearea.height
            contentWidth: (map.sizeX+1) * 64
            contentHeight: (map.sizeY+1) * 64
            boundsBehavior: Flickable.StopAtBounds
            Map {
                id:map
                width: gamearea.width
                height: gamearea.height
                x: maparea.contentX +7
                y: maparea.contentY +7
                cx: maparea.contentX
                cy: maparea.contentY
                MouseArea {
                    id :m
                    acceptedButtons:  Qt.AllButtons
                    width: gamearea.width
                    height: gamearea.height
                    onClicked: {
                        if (!map.rercActive){
                            if (mouse.button == Qt.RightButton && map.isFocusEmpty()&&map.isCellEmpty(mouseX,mouseY)&&
                                    map.isRecrPoss(mouseX,mouseY))
                            {
                                map.setLastxy(mouseX,mouseY)
                                recr.visible = true
                                map.rercActive = true
                                maparea.interactive = false

                            }

                            map.mouseClicked(mouseX,mouseY,mouse.button)
                            topPanel.update()
                            rightPanel.update()
                        }
                    }
                }
                onVictory: {
                    game.endGame()
                    gamearea.visible = false
                    rightPanel.visible = false
                    topPanel.visible = false
                    turnButton.visible = false
                    victoryScreen.visible = true
                }
                onDefeat: {
                    game.endGame()
                    gamearea.visible = false
                    rightPanel.visible = false
                    topPanel.visible = false
                    turnButton.visible = false
                    defeatScreen.visible = true
                }
                onAiturn: {
                    game.ait()
                }
            }

        }
    }
    Rectangle {
        id : recr
        onVisibleChanged: {
            content.update()
        }

        visible: false
        x:gamearea.width/2 -135
        y:gamearea.height/2 -90
        width: 270
        height: 180
        color: "#191D4A"

        Rectangle {
            id: recruitmentframe
            x:5
            y:5


            clip: true
            width: 260
            height: 140
            border {
                color: "grey"
                width: 2

            }
            color: "#003366"


            Recruitment {
                id : content
                m : map
                width : 260;
                height : 64*4
                x: -hbar.position * width
                y: -vbar.position * height
            }

            ScrollBar {
                id: vbar
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Vertical
                size: recruitmentframe.height / content.height
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }

            ScrollBar {
                id: hbar
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Horizontal
                size: recruitmentframe.width / content.width
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            MouseArea {
                width : parent.width -10
                height: parent.height -10
                onClicked: content.mouseClicked(mouseX+hbar.position * content.width,mouseY+vbar.position * content.height)
            }
        }
        Button {
            id : btn1
            x :10
            y :150
            width:100
            height: 20
            text: "Нанять"
            onClicked: {
                content.acceptr()
                map.rercActive = false
                recr.visible = false
                topPanel.update()
                maparea.interactive = true
            }
        }
        Button {
            x :120
            y :150
            width:100
            height: 20
            text: "Закрыть"
            onClicked: {
                map.rercActive = false
                recr.visible = false
                maparea.interactive = true
            }

        }
    }
    VictoryScreen {
        id: victoryScreen
        visible: false
    }
    DefeatScreen {
        id: defeatScreen
        visible: false
    }
}
