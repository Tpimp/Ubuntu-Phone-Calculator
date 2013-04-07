#include "equationproxy.hpp"
#include "../Backend/Composite/equation.hpp"


//NOTHING Fancy, call all the methods of the attached proxy method
// IF there is currently an equation attached - else dont

EquationProxy::EquationProxy()
{

}

void EquationProxy::attachProxy(Equation *equation)
{
    mEquation = equation;
}
void EquationProxy::detachProxy()
{
    mEquation = nullptr;
}

void EquationProxy::addOperand(Operand *operand, Operator *operation)
{
    if(mEquation)
        mEquation->addOperand(operand,operation);
}

void EquationProxy::clearEquation()
{
    if(mEquation)
        mEquation->clearEquation();
}


EquationProxy::~EquationProxy()
{

}
