import QtQuick 2.0

Rectangle {
    id: operation
    height: parent.height/4
    width: parent.width
    color: "#f7fb00"
    property alias op_text: operation_text
    Text
    {
        id: operation_text
        width: parent.width
        height: parent.height
        font.pixelSize: parent.height-4
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "black"
    }
}
