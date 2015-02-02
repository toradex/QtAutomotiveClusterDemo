import QtQuick 1.1


Image {
    id: progressBarLabel
    property color color;
    property string text;
    property string textLabel;

    source: "qrc:///label.png"
    anchors.horizontalCenter: parent.horizontalCenter

    Row {

        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5

        Text {
            text: progressBarLabel.textLabel
            color: "#575757"

            font.capitalization: Font.AllUppercase
            style: Text.Sunken
            styleColor: "white"
        }
        Text {
            text: progressBarLabel.text
            color: progressBarLabel.color

            font.capitalization: Font.AllUppercase
            style: Text.Sunken
            styleColor: "white"
        }
    }
}
