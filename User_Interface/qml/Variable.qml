import QtQuick 2.0
Rectangle
{
    color: "transparent"
    id:variable
    anchors.left: parent.left
    anchors.margins: 8
    height: parent.height
    property alias item_text:item_text
    MouseArea
    {
        id: mousearea
        anchors.fill: variable
        onClicked:
        {

            EventHandler.requestVariable(variable.objectName);
            console.log("Should be set",variable.objectName);
        }

    }
    Text
    {
        id:item_text
        text: "empty"
        color: "#fffc42"
        anchors.top: parent.top
        font.pixelSize: (parent.height - parent.height * .3)
        font.family: "Rockwell"
        styleColor: "#0c0966"
        style: Text.Outline
        onTextChanged: {variable.width = (text.length*font.pixelSize);}
        onWidthChanged: { variable.width = item_text.width;}
    }
    width: (item_text.width)
}
