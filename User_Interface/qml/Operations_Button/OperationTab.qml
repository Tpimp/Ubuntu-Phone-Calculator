import QtQuick 2.0

Rectangle {
    id: operationtab
    height: parent.height*.4
    width: parent.width*.3
    color: "transparent"
    property alias tab_button: tab_button
    property alias tab_column: tab_column
    property alias mouse_area: clickarea
    property alias plus: plus
    property alias subtract: subtract
    property alias multiply:multiply
    property alias divide: divide
    property int button_press: 0
    onWidthChanged:
    {
        tab_button.op_text.font.pixelSize = width/6;
    }

    Column
    {
        id: tab_column
        MouseArea
        {
            id: clickarea
            anchors.fill: tab_button
            onPositionChanged:
            {
                if(mouse.x >= 0 && mouse.x <=operationtab.width)
                {
                    button_press = (mouse.y-(divide.y/2-2))/(operationtab.tab_button.height);
                    //console.log("released on",button_press)
                    if(button_press == 4)
                    {
                        tab_button.color = "#08fbf7";
                        plus.color = "#f7fb00"
                        subtract.color = "#f7fb00";
                        multiply.color = "#f7fb00"
                        divide.color = "#f7fb00"
                    }
                    else if(button_press == 3)
                    {
                        tab_button.color = "#f7fb00";
                        plus.color = "#08fbf7";
                        subtract.color = "#f7fb00";
                        multiply.color = "#f7fb00"
                        divide.color = "#f7fb00"
                    }
                    else if(button_press == 2)
                    {
                        tab_button.color = "#f7fb00";
                        plus.color = "#f7fb00";
                        subtract.color = "#08fbf7";
                        multiply.color = "#f7fb00"
                        divide.color = "#f7fb00"
                    }
                    else if(button_press == 1)
                    {
                        tab_button.color = "#f7fb00";
                        plus.color = "#f7fb00";
                        subtract.color = "#f7fb00";
                        multiply.color = "#08fbf7"
                        divide.color = "#f7fb00"
                    }
                    else if(button_press == 0)
                    {
                        tab_button.color = "#f7fb00";
                        plus.color = "#f7fb00";
                        subtract.color = "#f7fb00";
                        multiply.color = "#f7fb00"
                        divide.color = "#08fbf7"
                    }
                    else
                    {
                        tab_button.color = "#f7fb00";
                        plus.color = "#f7fb00";
                        subtract.color = "#f7fb00";
                        multiply.color = "#f7fb00"
                        divide.color = "#f7fb00"
                    }
                }
                else
                {
                    tab_button.color = "#f7fb00";
                    plus.color = "#f7fb00";
                    subtract.color = "#f7fb00";
                    multiply.color = "#f7fb00"
                    divide.color = "#f7fb00"
                }
            }
        }
        anchors.fill: parent
        Operation
        {
            id:tab_button
            anchors.bottom: parent.bottom
            op_text.text: "Operations"
            border.color: "#f39106"

        }
        Operation
        {
            id:plus
            visible: false
            Image
            {
                height: parent.height-4
                width: height
                source: "qrc:/images/^+^.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            anchors.bottom: tab_button.top
            op_text.text: "+"
            border.color: "#000000"

        }
        Operation
        {
            id:subtract
            visible: false
            Image
            {
                height: parent.height-4
                width: height
                source: "qrc:/images/^-^.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.bottom: plus.top
            border.color: "#000000"

        }
        Operation
        {
            id:multiply
            visible: false
            Image
            {
                height: parent.height-4
                width: height
                source: "qrc:/images/^m^.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.bottom: subtract.top
            border.color: "#000000"

        }
        Operation
        {
            id:divide
            visible: false
            Image
            {
                height: parent.height-4
                width: height
                source: "qrc:/images/^d^.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
            anchors.bottom: multiply.top
            border.color: "#000000"
        }
    }
}
