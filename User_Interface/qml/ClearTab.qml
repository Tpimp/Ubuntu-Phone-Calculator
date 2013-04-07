import QtQuick 2.0

Rectangle {
    id: cleartab
    height: parent.height*.3
    width: parent.width*.3
    color: "transparent"
    property alias clear_button: tab_button
    property alias clear_column: tab_column
    property alias clear_mouse: clickarea
    property alias equation: equation
    property alias all: all
    property int press: 0
    onWidthChanged:
    {
        clear_button.item_text.font.pixelSize = width/6;
        //console.log("Height = ", clear_button.height)
    }

    Column
    {
        id: tab_column
        MouseArea
        {
            id: clickarea
            anchors.fill: cleartab.clear_button
            onPositionChanged:
            {
                if(mouse.x >= 0 && mouse.x <= (cleartab.x + cleartab.width))
                {
                    cleartab.press = (mouse.y - tab_button.height/2)/tab_button.height;
                    //console.log("hovered on",mouse.y)
                    if(cleartab.press == 1)
                    {
                        tab_button.color = "red"
                        equation.color = "yellow";
                        equation.item_text.color = "blue"
                        all.color = "green";
                    }
                    else if(cleartab.press == 0)
                    {
                        tab_button.color = "red";
                        equation.color = "blue";
                        equation.item_text.color = "yellow"
                        all.color = "yellow";
                    }
                    else
                    {
                        tab_button.color = "yellow";
                        equation.color = "blue";
                        equation.item_text.color = "yellow"
                        all.color = "green";
                    }
                }
            }
        }
        anchors.fill: parent
        TabItem
        {
            id:tab_button
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            item_text.text: "CLEAR"
            color: "red"
            border.color: "black"
        }
        TabItem
        {
            id:equation
            visible: false
            anchors.bottom: tab_button.top
            item_text.text: "Equation"
            border.color: "black"
            color: "blue"
            item_text.color: "yellow"

        }
        TabItem
        {
            id:all
            visible: false
            item_text.text: "All"
            color: "green"
            anchors.bottom: equation.top
            border.color: "black"

        }

    }
}
