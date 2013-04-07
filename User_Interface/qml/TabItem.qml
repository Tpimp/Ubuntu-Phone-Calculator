import QtQuick 2.0

Rectangle {
    id: tabitem
    height: parent.height/3
    width: parent.width
    color: "#f7fb00"
    property alias item_text: item_text
    Text
    {
        id: item_text
        width: parent.width
        height: parent.height
        font.pixelSize: parent.height-4
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "black"
    }
}
