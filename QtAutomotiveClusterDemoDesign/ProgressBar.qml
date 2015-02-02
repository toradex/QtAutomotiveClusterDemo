import QtQuick 1.1

Rectangle {
    property int progress: 0
    property string progressFillImage: "qrc:///progressbar_blue.png"
    property color borderColor: "#002a45"

    onProgressChanged:
    {
        imageProgress.width = progress * width / 100;
    }

    height: 18

    Rectangle {
        id: imageProgress
        border.color: borderColor
        border.width: 1
        radius: 1
        height: 17
        width: 0
        Image {
            anchors.left: parent.left
            anchors.leftMargin: 1
            anchors.top: parent.top
            anchors.topMargin: 1
            width: parent.width - 1
            height: 16
            fillMode: Image.TileHorizontally

            source: progressFillImage
        }
    }

    color: "#e3e3e3";
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#d8d8d8" }
        GradientStop { position: 0.2; color: "#e3e3e3"}
        GradientStop { position: 1.0; color: "#e3e3e3"}
    }
    radius: 1
    border.width: 1
    border.color: "#cecece"
}
