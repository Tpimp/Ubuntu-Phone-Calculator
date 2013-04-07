#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "operand.hpp"
class InFixInterpret;
class CalculationFlyWeight;
class Number : public Operand
{
    protected:
       friend class InFixInterpret;
       friend class CalculationFlyWeight;
       Number(QString* value);
       QString* mValue;
       ~Number();
    public:
       QString Solve();
};

#endif // NUMBER_HPP
