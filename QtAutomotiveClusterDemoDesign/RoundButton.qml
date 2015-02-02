import QtQuick 1.1

Rectangle {
    id: roundButton
    width: parent.buttonSize
    height: parent.buttonSize
    radius: parent.buttonSize*0.5
    state: "RELEASED"
/*
    property color upperColor: "#ff7474"
    property color lowerColor: "#d94e4e"
    property color borderColor: "#d94e4e"
    property int borderSize: 1
    property int buttonSize: 100
*/
    signal buttonClick()
    onButtonClick: {
        console.log(buttonLabel + " clicked" )
    }

    MouseArea {
        width: buttonSize
        height: buttonSize
        id: buttonMouseArea
        onClicked: buttonClick()
        hoverEnabled: true
        onPressed: parent.state = "PRESSED"
        onReleased: parent.state = "RELEASED"
        //onEntered: parent.border.color = onHoverColor
        //onExited:  parent.border.color = borderColor
    }

    states: [
        State {
            name: "PRESSED"
            PropertyChanges { target: idUpperColor; color: parent.lowerColor }
            PropertyChanges { target: idLowerColor; color: parent.upperColor }
        },
        State {
            name: "RELEASED"
            PropertyChanges { target: idUpperColor; color: parent.upperColor }
            PropertyChanges { target: idLowerColor; color: parent.lowerColor }
        }
    ]

    transitions: [
        Transition {
            from: "PRESSED"
            to: "RELEASED"
            ColorAnimation { target: idUpperColor; duration: 100}
            ColorAnimation { target: idLowerColor; duration: 100}
        },
        Transition {
            from: "RELEASED"
            to: "PRESSED"
            ColorAnimation { target: idUpperColor; duration: 100}
            ColorAnimation { target: idLowerColor; duration: 100}
        }
    ]

    gradient: Gradient {
        GradientStop { id: idUpperColor; position: 0.0; color: parent.upperColor }
        GradientStop { id: idLowerColor; position: 1.0; color: parent.lowerColor }
    }


    border.width: parent.borderSize
    border.color: parent.borderColor
    smooth: true
}
