#include "operand.hpp"

Operand::Operand(Expression type)
    : mExpression(type) // initialize expression
{}

// Check if operator precedence is less than rhs
bool Operand::operator <(Operand& RHS)
{
    if(this->mExpression < DIVIDE && RHS.mExpression >= DIVIDE)
    {
        return true;
    }
    return false;
}

// Check if they are of equivalent precedence
bool Operand::operator ==(Operand& RHS)
{
    if(this->mExpression < DIVIDE && RHS.mExpression < DIVIDE)
    {
        return true;
    }
    else if (this->mExpression >= DIVIDE && RHS.mExpression >= DIVIDE)
    {
        return true;
    }
    return false;
}

Operand::~Operand()
{
    mExpression = NUMBER;// clear expression
}
