#ifndef EQUATION_HPP
#define EQUATION_HPP

#include "../Backend/Globals/globals.hpp"
#include "../Backend/Globals/exceptions.hpp"
#include "../Backend/Proxy/iequation.hpp"
#include "operand.hpp"
#include "variable.hpp"
#include "operator.hpp"
// define states


class Equation : public Var, iEquation
{

    protected:
        Operator*& findTarget(Operator*& op);
    public:
        Equation(CalculationFlyWeight& flyweight,QString& name,
                 QString& user_string, Operand* root = nullptr);
        void addOperand(Operand* operand, Operator* operation = nullptr);
        void removeRearItem();
        void clearEquation();
        ~Equation();
};

#endif // EQUATION_HPP
