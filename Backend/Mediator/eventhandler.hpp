#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <QObject>
#include <QQmlContext>
//#include <QDebug> // Ony when using qDebug() for output

// include composite items that Event Handler will work with
#include "../Backend/Composite/equation.hpp"
#include "../Backend/Composite/variable.hpp"
#include "../Backend/Composite/operand.hpp"
#include "../Backend/Composite/operator.hpp"
// Include defined proxy interface and implementation of variable and equation
#include "../Backend/Proxy/equationproxy.hpp"
#include "../Backend/Proxy/variableproxy.hpp"


class CalculationFlyWeight;

// Input Event Handler manages the connections between the User inteface,
// and the backend logic of the calculator.
// This is possible through the QML Binding capabilities and the Q_INVOKABLE
// methods.
class InputEventHandler : public QObject
{
    Q_OBJECT

    protected:
           VariableProxy mVariable;
           EquationProxy mEquation;
           CalculationFlyWeight* mFlyweight;
           QQmlContext* mQmlContext;
           // protected helper methods for Internal use only
           void addOperand(Operator* operation);
           void clearEquation();
           void setVariable(QString name);
           void setVariableName(QString new_name);
           void setVariableEquation(QString new_equation);
           void setVariableRoot(Operand* root);
           void solveVariable();
    public:
           InputEventHandler( CalculationFlyWeight* flyweight,
                             QQmlContext* textinput,QObject* parent = 0,
                             Equation* equation = nullptr,Var* variable = nullptr);


           // Q_INVOKABLE allows the functions to be called from QML
           Q_INVOKABLE void requestVariableClear()
           {
               clearEquation();
           }

           Q_INVOKABLE void solveEquation(const QString& equation)
           {
               setVariableEquation(equation);
               solveVariable();
           }

           Q_INVOKABLE void requestVariable(const QString& name)
           {
               this->setVariable(name);
           }

           ~InputEventHandler();
    
};

#endif // EVENTHANDLER_HPP
