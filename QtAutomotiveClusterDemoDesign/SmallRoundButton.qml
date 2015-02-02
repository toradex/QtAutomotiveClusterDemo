import QtQuick 1.1

/*
 * Small round button with only one line of text...
 */
Rectangle {
    width: buttonSize
    height: buttonSize
    radius: buttonSize*0.5

    property string buttonLabel: "QUIT"

    property color upperColor: "#ff7474"
    property color lowerColor: "#d94e4e"
    property color borderColor: "#d94e4e"
    property int borderSize: 1
    property int buttonSize: 100

    signal buttonClick()

    RoundButton {
        anchors.centerIn: parent
        Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter;
            text: buttonLabel
            font.pixelSize: 20
            font.bold: true
            font.capitalization: Font.AllUppercase
            style: Text.Sunken
            styleColor: "black"

            color: "white"
        }

        onButtonClick: {
            parent.buttonClick();
        }
    }
}
