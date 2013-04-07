#ifndef EQUATIONPROXY_HPP
#define EQUATIONPROXY_HPP

#include "iequation.hpp"

class Equation;
//*****************************************************************************
// Equation Proxy "attaches" to an equation and then utilizes its methods.
// When necessary the equation will be detached from the proxy and then another
// equation will be attached in it's place. The equation current attached will
// be represented in the equation display (see CurrentFunction.qml)
//******************************************************************************
class EquationProxy : public iEquation
{
    protected:
        Equation * mEquation; // pointer to store current equation address
    public:
        EquationProxy();
        // Proxy methods
        void addOperand(Operand* operand, Operator* operation = nullptr);
        void attachProxy(Equation* equation);
        void clearEquation();
        void detachProxy();
        ~EquationProxy();
};

#endif // EQUATIONPROXY_HPP
