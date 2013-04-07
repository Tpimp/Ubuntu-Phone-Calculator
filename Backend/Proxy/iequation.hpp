#ifndef IEQUATION_HPP
#define IEQUATION_HPP

#include "../Backend/Composite/operand.hpp"
#include "../Backend/Composite/operator.hpp"
#include "../Backend/Composite/variable.hpp"

// Defines an interface class to for the Equation Proxy Pattern
class iEquation
{
    public:
        virtual void addOperand(Operand* operand,
                                Operator* operation = nullptr) = 0;
        virtual void clearEquation() = 0;
};


#endif // IEQUATION_HPP
