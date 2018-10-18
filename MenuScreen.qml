import QtQuick 2.0
import QtQuick.Controls 2.0
import menu 1.0

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
        Text {
            x: 100
            y: 100
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Выберите карту: "
        }
        Text {
            x: 100
            y: 200
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Игрок1: "
        }Text {
            x: 100
            y: 300
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Игрок2: "
        }Text {
            x: 100
            y: 400
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Игрок3: "
        }Text {
            x: 100
            y: 500
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Игрок4: "
        }
        Text {
            x: 550
            y: 200
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Базовый доход: "
        }Text {
            x: 550
            y: 300
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Базовый доход: "
        }Text {
            x: 550
            y: 400
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Базовый доход: "
        }Text {
            x: 550
            y: 500
            width: 140
            horizontalAlignment: Text.AlignRight
            color: "white"
            font.pointSize: 12
            text : "Базовый доход: "
        }
        ComboBox {
            id :mapChoose
            x: 250
            y: 100
            width: 200
            model: ListModel {
                ListElement { text: "First map" }
                ListElement { text: "Second map" }
                ListElement { text: "Third map"}
            }
            onCurrentTextChanged: menu.s_map=currentText
        }
        ComboBox {
            id :firstPlChoose
            x: 250
            y: 200
            width: 200
            model: ListModel {
                ListElement { text: "Cult" }
                ListElement { text: "Inc" }

            }
            onCurrentTextChanged: menu.pf1=currentText
        }
        ComboBox {
            id :secPlChoose
            x: 250
            y: 300
            width: 200
            model: ListModel {
                ListElement { text: "Inc" }
                ListElement { text: "Cult" }

            }
            onCurrentTextChanged: menu.pf2=currentText
        }
        ComboBox {
            id :thirdPlChoose
            x: 250
            y: 400
            width: 200
            model: ListModel {
                ListElement { text: "None"}
                ListElement { text: "Cult" }
                ListElement { text: "Inc" }

            }
            onCurrentTextChanged: menu.pf3=currentText
        }
        ComboBox {
            id :fourthPlChoose
            x: 250
            y: 500
            width: 200
            model: ListModel {
                ListElement { text: "None"}
                ListElement { text: "Inc" }
                ListElement { text: "Cult" }

            }
            onCurrentTextChanged: menu.pf4=currentText
        }
        ComboBox {
            id :firstBIChoose
            x: 750
            y: 200
            width: 200
            model: ListModel {
                ListElement { text: "0"}
                ListElement { text: "5"}
                ListElement { text: "10"}
                ListElement { text: "15"}
            }
            onCurrentTextChanged: menu.bi1=currentText
        }
        ComboBox {
            id :secBIChoose
            x: 750
            y: 300
            width: 200
            model: ListModel {
                ListElement { text: "0"}
                ListElement { text: "5"}
                ListElement { text: "10"}
                ListElement { text: "15"}

            }
            onCurrentTextChanged: menu.bi2=currentText
        }
        ComboBox {
            id :thirdBIChoose
            x: 750
            y: 400
            width: 200
            model: ListModel {
                ListElement { text: "0"}
                ListElement { text: "5"}
                ListElement { text: "10"}
                ListElement { text: "15"}
            }
            onCurrentTextChanged: menu.bi3=currentText
        }
        ComboBox {
            id :fourthBIChoose
            x: 750
            y: 500
            width: 200
            model: ListModel {
                ListElement { text: "0"}
                ListElement { text: "5"}
                ListElement { text: "10"}
                ListElement { text: "15"}
            }
            onCurrentTextChanged: menu.bi4=currentText
        }
        Menu {
            id : menu
            s_map: "1"
            pf1: "Cult"
            pf2: "Inc"
            pf3: "None"
            pf4: "None"
            bi1: "0"
            bi2: "0"
            bi3: "0"
            bi4: "0"
            Component.onCompleted:
            {
                game.mn = menu
            }
        }
    }

}
