#ifndef OPERAND_HPP
#define OPERAND_HPP


#include "../Backend/Globals/globals.hpp"
#include <QString>
#include "../Backend/Flyweight/calculationflyweight.hpp"
#include "../ttmath/ttmath.h"
class InFixInterpret;
class Operand
{
    protected:
        //friend class InFixInterpret;
        friend class CalculationFlyWeight;
        Expression mExpression;
        Operand(Expression type = NUMBER);
        ~Operand();
    public:
        bool operator <(Operand& RHS);
        bool operator ==(Operand& RHS);
        virtual QString Solve() = 0;
};

#endif // OPERAND_HPP
