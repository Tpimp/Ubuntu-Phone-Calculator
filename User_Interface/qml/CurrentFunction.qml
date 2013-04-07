import QtQuick 2.0

BorderImage{
    id:currentfunction
    height: (parent.height * .05)
    width: (parent.width * 0.54)
    source: "qrc:/images/qml/images/lineedit.png"
    border.left:5
    border.right:5
    border.top:5
    border.bottom:5
    z: 2
    property var mLastAdded: null
    function addOperand(name,new_text)
    {
        var new_var_comp = Qt.createComponent("Variable.qml");
        var my_variable;
        if(mLastAdded == null)
        {

            my_variable = new_var_comp.createObject(equationrow,{ "id": name,
                                                                 "objectName": name,
                                                                 "item_text.text": new_text,
                                                                 "anchors.left": equationrow.left });
        }
        else
        {
            my_variable = new_var_comp.createObject(equationrow,{ "id": name,
                                                                 "objectName": name,
                                                                 "item_text.text": new_text,
                                                                 "anchors.left": mLastAdded.right });
        }
        mLastAdded = my_variable;
    }
    Flickable
    {
        id: flickable
        width: parent.width
        height: parent.height
        clip: true
        flickableDirection: Flickable.HorizontalFlick
        Row
        {
           anchors.fill: parent
           anchors.leftMargin: 4
           anchors.topMargin: 6
           height: parent.height
           spacing: 12
           id: equationrow
           onChildrenChanged: {flickable.contentWidth = mLastAdded != null ?(mLastAdded.x + mLastAdded.width):0;}
        }
        contentWidth: width
        contentHeight: height
    }
}


