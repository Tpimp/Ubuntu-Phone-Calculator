import QtQuick 2.0

BorderImage {
    id:numberdisplay
    height: (parent.height * 0.80 )
    width: (parent.width * 0.76)
    source: "qrc:/images/qml/images/lineedit.png"
    border.left:5
    border.right:5
    border.top:5
    border.bottom:5
    //anchors.horizontalCenter: parent.border.left
    property alias text:input
    property alias cursorposition:input.cursorPosition
    property int lastPosition: 0
    function insertText(input_text)
    {
        lastPosition = cursorposition
        text.insert(cursorposition, input_text)
        cursorposition = lastPosition+1
    }

    Flickable
    {
        id: flickable
        width: parent.width
        height: parent.height
        contentWidth: input.paintedWidth
        contentHeight: input.paintedHeight
        clip: true
        flickableDirection: Flickable.VerticalFlick
        function ensureVisible(r)
        {
                 if (contentX >= r.x)
                     contentX = r.x;
                 else if (contentX+width <= r.x+r.width)
                     contentX = r.x+r.width-width;
                 if (contentY >= r.y)
                     contentY = r.y;
                 else if (contentY+height <= r.y+r.height)
                     contentY = r.y+r.height-height;
        }

        TextEdit{
            id: input
            //textFormat: TextEdit.RichText
            font.pixelSize: (numberdisplay.parent.height + numberdisplay.parent.width) /32
            activeFocusOnPress: true
            text: VariableText
            horizontalAlignment: TextInput.AlignLeft
            font.family: "Pocket Calculator"
            anchors.margins: 4
            wrapMode: TextEdit.Wrap
            width:numberdisplay.width
            height:numberdisplay.height
            onCursorRectangleChanged: flickable.ensureVisible(cursorRectangle)
        }
    }

}
