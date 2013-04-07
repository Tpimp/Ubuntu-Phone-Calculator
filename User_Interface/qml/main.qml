import QtQuick 2.0
import "Operations_Button"
Rectangle {
    id:myscreen
    width: 720
    height: 1280
    color: "black"
   // anchors.left: screen.left
   // anchors.right: screen.right
   // anchors.top: screen.top
   // anchors.bottom: screen.bottom

    CurrentFunction
    {
        id:mCurrentfunction
        anchors.top: myscreen.top
        anchors.left: myscreen.left
        focus: true
       // text.font.pixelSize: (text.height + text.width)/18
    }

    OperationTab
    {
        id: op_tab
        anchors.left: myscreen.left
        anchors.bottom: mNumberDisplay.bottom
        anchors.bottomMargin: -(height/4)
        z:2
        mouse_area.onPressed:
        {
            op_tab.plus.visible = true;
            op_tab.subtract.visible = true;
            op_tab.multiply.visible = true;
            op_tab.divide.visible = true;
            mouse_area.anchors.fill = op_tab.tab_column
        }
        mouse_area.onReleased:
        {
            op_tab.plus.visible = false;
            op_tab.subtract.visible = false;
            op_tab.multiply.visible = false;
            op_tab.divide.visible = false;
            if(mouse.x >= op_tab.x && mouse.x <= (op_tab.x + op_tab.width))
            {
                op_tab.button_press = (mouse.y-(divide.y/2-2))/(op_tab.tab_button.height);
                //console.log("released on",button_press)

                if(op_tab.button_press == 3)
                {
                    mNumberDisplay.text.insert(mNumberDisplay.cursorposition,"^+^")
                }
                else if(op_tab.button_press == 2)
                {
                    mNumberDisplay.text.insert(mNumberDisplay.cursorposition,"^-^")
                }
                else if(op_tab.button_press == 1)
                {
                    mNumberDisplay.text.insert(mNumberDisplay.cursorposition,"^*^")
                }
                else if(op_tab.button_press == 0)
                {
                    mNumberDisplay.text.insert(mNumberDisplay.cursorposition,"^/^")
                }
            }

        mouse_area.anchors.fill = op_tab.tab_button
        }

    }


    ClearTab
    {
        id: clear_tab
        anchors.left: op_tab.right
        anchors.bottom: mNumberDisplay.bottom
        anchors.bottomMargin: -(height/3)
        z:2
        clear_mouse.onPressed:
        {
            clear_tab.equation.visible = true;
            clear_tab.all.visible = true;
            clear_mouse.anchors.fill = clear_tab.clear_column
            clear_tab.clear_button.color = "yellow";
        }
        clear_mouse.onReleased:
        {
            clear_tab.equation.visible = false;
            clear_tab.all.visible = false;
            //console.log("Released at", mouse.y)
            if(mouse.x >= 0 && mouse.x <= clear_tab.width)
            {
                clear_tab.press = (mouse.y- clear_tab.clear_button.height/2)/(clear_tab.clear_button.height);
                //console.log("released on",clear_tab.press)

                if(clear_tab.press == 1)
                {
                    // send variable clear request
                    EventHandler.requestVariableClear()
                }
                else if(clear_tab.press == 0)
                {
                    // impliment clear request equation
                   // mNumberDisplay.text.insert(mNumberDisplay.cursorposition,"^/^")
                }
            }
            clear_button.color = "red";
            clear_mouse.anchors.fill = clear_tab.clear_button
        }

    }

    Button
    {
        id: calculate
        anchors.top: myscreen.top
        anchors.left: mCurrentfunction.right
        height : (myscreen.height * .05)
        width: (myscreen.width * .22)
        text.text:"calculate"
        onWidthChanged: {text.font.pixelSize= parent.width * .03}

        MouseArea {
            id:click_calculate
            anchors.fill: parent
            onClicked:
            {
                // get calculation
                //console.log("Sending", mNumberDisplay.text.text)
                EventHandler.solveEquation(mNumberDisplay.text.text)
            }
        }
    }

    VarNameBar
    {
        id:mNameBar
        anchors.top: mCurrentfunction.bottom
        anchors.left: myscreen.left
    }

    Button
    {
        id:zero
        text.text:"0"
        anchors.left: mNumberDisplay.right
        anchors.top: parent.top
        MouseArea {
            id:clickareazero
            anchors.fill: parent
            onClicked:
            {
                mNumberDisplay.insertText(zero.text.text)
            }
        }

    }
    Button
    {
        id:one
        text.text:"1"
        anchors.top: parent.top
        anchors.right: parent.right
        MouseArea {
            id:clickareaone
            anchors.fill: parent
            onClicked:
            {
                 mNumberDisplay.insertText(one.text.text)
            }
        }
    }
    Button
    {
        id:two
        text.text:"2"
        anchors.left: mNumberDisplay.right
        anchors.top: zero.bottom
        MouseArea {
            id:clickareatwo
            anchors.fill: parent
            onClicked:
            {
                mNumberDisplay.insertText(two.text.text)
            }
        }
    }
    Button
    {
        id:three
        text.text:"3"
        anchors.top: one.bottom
        anchors.right: parent.right
        MouseArea {
            id:clickareathree
            anchors.fill: parent
            onClicked:
            {
                mNumberDisplay.insertText(three.text.text)
            }
        }
    }
    Button
    {
        id:four
        text.text:"4"
        anchors.left: mNumberDisplay.right
        anchors.top: two.bottom
        MouseArea {
            id:clickareafour
            anchors.fill: parent
            onClicked:
            {
                mNumberDisplay.insertText(four.text.text)
            }
        }
    }
    Button
    {
        id:five
        text.text:"5"
        anchors.top: three.bottom
        anchors.right: parent.right
        MouseArea {
            id:clickareafive
            anchors.fill: parent
            onClicked:
            {
                mNumberDisplay.insertText(five.text.text)
            }
        }
    }
    Button
    {
        id:six
        text.text: "6"
        anchors.left: mNumberDisplay.right
        anchors.top: four.bottom
        MouseArea {
            id:clickareasix
            anchors.fill: parent
            onClicked:
            {
                mNumberDisplay.insertText(six.text.text)
            }
        }
    }
    Button
    {
        id:seven
        text.text:"7"
        anchors.top: five.bottom
        anchors.right: parent.right
        MouseArea {
            id:clickareaseven
            anchors.fill: parent
            onClicked: { mNumberDisplay.insertText(seven.text.text) }
        }
    }
    Button
    {
        id:eight
        text.text:"8"
        anchors.left: mNumberDisplay.right
        anchors.top: six.bottom
        MouseArea {
            id:clickareaeight
            anchors.fill: parent
            onClicked: { mNumberDisplay.insertText(eight.text.text) }
        }
    }
    Button
    {
        id:nine
        text.text:"9"
        anchors.top: seven.bottom
        anchors.right: parent.right
        MouseArea {
            id:clickareanine
            anchors.fill: parent
            onClicked: { mNumberDisplay.insertText(nine.text.text) }
        }
    }

    Button
    {
        id:decimal
        text.text:"."
        anchors.top: eight.bottom
        anchors.left: mNumberDisplay.right
        MouseArea {
            id:clickareadecimal
            anchors.fill: parent
            onClicked: { mNumberDisplay.insertText(decimal.text.text) }
        }
    }
    Button
    {
        id:neg
        text.text:"(-)"
        anchors.top: nine.bottom
        anchors.right: parent.right
        onWidthChanged: { neg.text.font.pixelSize = (text.height + text.width)/3}
        MouseArea {
            id:clickareaneg
            anchors.fill: parent
            onClicked: { mNumberDisplay.insertText('-') }
        }
    }

    NumberDisplay
    {
        anchors.top: mNameBar.bottom
        anchors.left: myscreen.left
        id:mNumberDisplay
        z:1
    }
}
