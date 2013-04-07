#include "function.hpp"
#include <QDebug>
Function::Function(Expression type, QList<Operand *> &parameters) :
    Operand(type), mParameters(parameters)
{
}

QString Function::PerformFunction()
{
    QString return_val;
    switch(mExpression) // Switch on Type
    {
        case ABSOLUTE :{ttmath::Big<2,4> // if ABS
                    val(mParameters[0]->Solve().toStdWString());
                    val.Abs(); // perform function
                    return_val = val.ToString().data();
                    break;
                   }
                  // create left and right
        case MIN :{ttmath::Big<1,2> left(mParameters[0]->Solve().toStdWString());
               ttmath::Big<1,2> right(mParameters[1]->Solve().toStdWString());
               if(right < left)
                   left = right; // perform operation
               return_val = left.ToString().data();
               break;
              }
                // create left and right then compare for max
        case MAX :{ttmath::Big<1,2> left(mParameters[0]->Solve().toStdWString());
                  ttmath::Big<1,2> right(mParameters[1]->Solve().toStdWString());
                  left = (right > left ? right:left);
                  return_val = left.ToString().data();
                  break;
                 }
         default:{break;}
    }
    return return_val; // return the result
}

QString Function::Solve()
{
    return PerformFunction(); // return result out
}

Function::~Function()
{
    // dump paramater list
    mParameters.clear();
}
