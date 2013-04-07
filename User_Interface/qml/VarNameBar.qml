import QtQuick 2.0

BorderImage
{
    id:top_level
    height: (parent.height * .05)
    width: (parent.width * 0.76)
    source: "qrc:/images/qml/images/lineedit.png"
    border.left:5
    border.right:5
    border.top:5
    border.bottom:5
    property alias titleText:title
    property alias varName:name_str
    Rectangle
    {
        id: frame_rect
        color: "black"
        height: parent.height
        width: parent.width/3
        Rectangle
        {
            color:"yellow"
            anchors.fill: parent
            anchors.margins: parent.height*.05
            Text
            {
                id: title
                height: parent.height
                width: parent.width
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.height - parent.height*.3
                font.family: "Britannic Bold"
                color: "black"
                text: "Variable Name:"
                onWidthChanged:{ frame_rect.width = paintedWidth+ parent.width*.1;}
            }

        }
    }
    Rectangle
    {
        anchors.top: top_level.top
        height: top_level.height
        x: frame_rect.x + frame_rect.width
        width: top_level.width-frame_rect.width
        anchors.bottomMargin: parent.height*.5
        color: "transparent"
        border.color: "#000000"
        border.width: parent.height*.05
        Text
        {
            anchors.fill: parent
            anchors.margins: parent.height*.2
            id: name_str
            verticalAlignment:  Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: top_level.height - top_level.height*.3
            color: "yellow"
            text: VariableName
            font.family: "Footlight MT Light"
            font.bold: true
            font.italic: true
            z:2
        }
    }
}
