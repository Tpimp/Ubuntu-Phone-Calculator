#include "operator.hpp"
Operator::Operator(Expression type, Operand *right, Operand *left) :
    Operand(type), mRight(right), mLeft(left)
{}

QString Operator::PerformOperation()
{
    ttmath::Big<1,2> result;
    switch(mExpression)
    {
        case PLUS: { result = // ADD
                     ttmath::Big<1,2>(mLeft->Solve().toStdWString()) +
                     ttmath::Big<1,2>(mRight->Solve().toStdWString());
                     break;
                   }
        case SUBTRACT: { result = // SUBTRACT
                 ttmath::Big<1,2>(mLeft->Solve().toStdWString()) -
                 ttmath::Big<1,2>(mRight->Solve().toStdWString());
                 break;
               }
         case MULTIPLY: { result = // MULTIPLY
                 ttmath::Big<1,2>(mLeft->Solve().toStdWString()) *
                 ttmath::Big<1,2>(mRight->Solve().toStdWString());
                 break;
               }
         case DIVIDE: { result = // DIVIDE
                 ttmath::Big<1,2>(mLeft->Solve().toStdWString()) /
                 ttmath::Big<1,2>(mRight->Solve().toStdWString());
                 break;
               }
        default : {break;}
    }
    return QString(result.ToString().data()); // return the result
}

QString Operator::Solve()
{
    return PerformOperation(); // call operation and return result
}

Operator::~Operator()
{
    mRight = nullptr; // null ptrs
    mLeft = nullptr;
}
