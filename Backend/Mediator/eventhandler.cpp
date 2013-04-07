#include "eventhandler.hpp"
#include "../Backend/Composite/equation.hpp"
#include "../Backend/Flyweight/calculationflyweight.hpp"
#include <QDebug>


InputEventHandler::InputEventHandler(CalculationFlyWeight *flyweight, QQmlContext *textinput, QObject *parent, Equation *equation, Var *variable) :
    QObject(parent), mFlyweight(flyweight), mQmlContext(textinput)
{
    // attach proxies if they exist, else attach to nullptr
    mEquation.attachProxy(equation);
    mVariable.attachProxy(variable);
   // if valid pointers set their data
    if(variable)
    {
        // update the editor display text (In the QML User Interface NumberDisplay.qml)
        mQmlContext->setContextProperty("VariableText",variable->getEquation());
        // update the variable name text (In the QML User Interface VarNameBar.qml)
        mQmlContext->setContextProperty("VariableName",variable->getName());
    }
}

void InputEventHandler::addOperand(Operator *operation)
{
   // handle adding an operand request fro the User (Finished button clicked)
   // Not yet implemnted in UI
   mEquation.addOperand(mVariable.getAttachedVar(),operation);
}


void InputEventHandler::clearEquation()
{
    // Set the varibale text to ""
    mQmlContext->setContextProperty("VariableText",QString());
}

void InputEventHandler::setVariable(QString name)
{
    // request the Operandby OBJ from the flyweight (Operand*), then
    // cast it back to a Variable. (getOperandObj just cast it to an Operand*)
    Var* new_var = reinterpret_cast<Var*>(mFlyweight->getOperandObj(name));
    qDebug() << new_var->getName();
    // next attach the proxy
    mVariable.attachProxy(new_var);
    // update the editor display text (In the QML User Interface NumberDisplay.qml)
    mQmlContext->setContextProperty("VariableText",new_var->getEquation());
    // update the variable name text (In the QML User Interface VarNameBar.qml)
    mQmlContext->setContextProperty("VariableName",new_var->getName());
}
void InputEventHandler::solveVariable()
{
    // update the editor display text (In the QML User Interface NumberDisplay.qml)
    Var* new_var = reinterpret_cast<Var*>(mVariable.getAttachedVar());
    mQmlContext->setContextProperty("VariableText",reinterpret_cast<Var*>(mVariable.getAttachedVar())->Solve());
    // update the variable name text (In the QML User Interface VarNameBar.qml)
    mQmlContext->setContextProperty("VariableName","ANSWER");
}

void InputEventHandler::setVariableEquation(QString new_equation)
{
    // Update the variables binary expression tree to represent the new equation
    mVariable.setEquation(new_equation);
}

void InputEventHandler::setVariableName(QString new_name)
{
    // update the name using the proxy method
    mVariable.setName(new_name);
}

void InputEventHandler::setVariableRoot(Operand *root)
{
    mVariable.setRoot(root); // call set root on the proxy
}



InputEventHandler::~InputEventHandler()
{
    // proxies clear themselves
}
