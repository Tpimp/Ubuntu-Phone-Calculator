#include "number.hpp"

Number::Number(QString *value) :
    Operand()
{
   mValue = value; //store a copy
}




QString Number::Solve()
{
    QString return_val;
    if(mValue) // pointer is valid
        return_val = *mValue; //return value
    return return_val; //else return ""
}


Number::~Number()
{
    mValue = nullptr; // null ptr
}
