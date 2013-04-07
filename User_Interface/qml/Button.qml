import QtQuick 2.0

Rectangle {
    id:button
    onWidthChanged: {
           var button_width = (width)/(buttontext.text.length)
           var button_height = (height)/(buttontext.text.length)
           buttontext.font.pixelSize = (button_width > button_height ? button_height-4:button_width-4);}
    width: parent.width * 0.119
    height: parent.height * 0.126
    color: "black"
    border.width: 3
    radius: 8
    border.color: "white"
    property alias text:buttontext
    signal pressed(string text)

    Text{
        id:buttontext
        width:parent.width
        height: parent.height
        font.family: "Pocket Calculator"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text:"0"
        font.pixelSize: 60
        font.bold: true
        color: "white"
    }
}
