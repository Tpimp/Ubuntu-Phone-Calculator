#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "operand.hpp"
class InFixInterpret;
class CalculationFlyWeight;
class Equation;
class Operator : public Operand
{
    protected:
        friend class InFixInterpret;
        friend class CalculationFlyWeight;
        friend class Equation;
        Operand* mRight;
        Operand* mLeft;
        Operator(Expression type, Operand* right = nullptr,
                 Operand* left = nullptr);
        QString PerformOperation();
        ~Operator();
    public:
        QString Solve();

};

#endif // OPERATOR_HPP
