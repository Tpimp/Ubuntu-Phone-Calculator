#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "operand.hpp"

#include <QList>

class InFixInterpret;
class CalcualtionFlyWeight;
class Function : public Operand
{
    protected:
       friend class CalculationFlyWeight;
       friend class InFixInterpret;
       QList<Operand*> mParameters;
       Function(Expression type, QList<Operand*>& parameters);
       QString PerformFunction();
       ~Function();
     public:
       QString Solve();
};

#endif // FUNCTION_HPP
