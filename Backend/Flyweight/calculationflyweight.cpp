#include "calculationflyweight.hpp"
#include "../Backend/Composite/operand.hpp"
#include "../Backend/Composite/number.hpp"
#include "../Backend/Composite/operator.hpp"
#include "../Backend/Composite/function.hpp"
#include "../Backend/Composite/variable.hpp"
#include "../Backend/Interpreter/infixinterpret.hpp"
#include <QDebug>
CalculationFlyWeight::CalculationFlyWeight()
{
   // initialize CalculationFlyweight with a ZERO value
    Var* temp = nullptr;
    insertCalculation("0","ZERO",temp);
}

QString CalculationFlyWeight::insertCalculation(QString calculation,
                                                QString name,
                                                Var *&previous)
{
   QString token_name;
   if(previous)
   {
       //TODO : Show Lazy initialization
       if(calculation.compare(previous->mUserString))
       {
           previous->mUserString = calculation;
           QString token = InFixInterpret::Evaluate(calculation,*this);
           previous->mRoot = getOperandObj(token);
           if(name.compare(previous->mName))
           {
               QString value(mCalculationTable[previous->mName]);
               mCalculationTable.remove(previous->mName);
               mCalculationTable.insert(name,value);
               token_name = value;
           }
       }
       else
       {
           if(name.compare(previous->mName))
           {
               QString value(mCalculationTable[previous->mName]);
               mCalculationTable.remove(previous->mName);
               mCalculationTable.insert(name,value);
               token_name = value;
           }
       }
   }
   else
   {

       //if name exists so does variable data
       if(mCalculationTable.contains(name))
       {
           token_name = mCalculationTable[name];
           if(calculation.compare(previous->mUserString))
           {
               previous->mUserString = calculation;
               previous->mRoot  = getOperandObj(InFixInterpret::Evaluate(calculation,*this));
               if(name.compare(previous->mName))
               {
                   QString value(mCalculationTable[previous->mName]);
                   mCalculationTable.remove(previous->mName);
                   mCalculationTable.insert(name,value);
               }
           }
       }
       else
       {
           Operand* root = getOperandObj(InFixInterpret::Evaluate(calculation,*this));
           // create a new variable

           previous = new Var(*this,name,calculation,root);
           int variable_count = mVariableOperands.size();
           token_name =("V"+QString::number(variable_count));
           mCalculationTable.insert(name, token_name);
           mVariableOperands.append(previous);
           qDebug() << "Creating " << name << "with token " << token_name;
       }
   }
   return token_name;

}


QString CalculationFlyWeight::addNumber(QString value)
{
    QString new_token;
    //TODO show Lazy initialization of number
    if(!mCalculationTable.contains(value))
    {
        new_token = ("N" + QString::number(mNumberOperands.size()));
        QString* ptr = new QString(value);
        Number* num(new Number(ptr));
        QPair<QString*,Number*> pair;
        pair.first = ptr;
        pair.second = num;
        mNumberOperands.append(pair);
        mCalculationTable.insert(value,new_token);
    }
    else
    {
        new_token = mCalculationTable[value];
        QPair<QString*,Number*> pair(mNumberOperands.at(new_token.section("",1).toInt()));
    }
    return new_token;
}

QString CalculationFlyWeight::addOperator(QString operator_str, QString left,
                                          QString right)
{
    Operand* left_ptr;
    Operand* right_ptr;
    QString new_token;
    // TODO Show lazy initializtion of operator
    if(left[0].isDigit())
    {
        if(!mCalculationTable.contains(left))
        {
            new_token = ("N" + QString::number(mNumberOperands.size()));
            QString* ptr = new QString(left);
            Number* left_num =new Number(ptr);
            left_ptr = reinterpret_cast<Operand*>(left_num);
            QPair<QString*,Number*> pair;
            pair.first = ptr;
            pair.second = left_num;
            mNumberOperands.append(pair);
            mCalculationTable.insert(left,new_token);
        }
        else
        {
            new_token = mCalculationTable[left];
            // get number's index
            int index = new_token.section("",1).toInt();
            // get the number operand
            QPair<QString*,Number*> pair = mNumberOperands.at(index);
            Number* number = pair.second;
            left_ptr = reinterpret_cast<Operand*>(number);
        }
        operator_str.replace(left,new_token);
    }
    else // else if its a value in the
    {
        left_ptr = getOperandObj(left);
    }
    if(right[0].isDigit())
    {
        if(!mCalculationTable.contains(right))
        {
            new_token = ("N" + QString::number(mNumberOperands.size()));
            QString* ptr = new QString(right);
            Number* right_num = new Number(ptr);
            right_ptr = reinterpret_cast<Operand*>(right_num);
            QPair<QString*,Number*> pair;
            pair.first = ptr;
            pair.second = right_num;
            mNumberOperands.append(pair);
            mCalculationTable.insert(right,new_token);
        }
        else
        {
            new_token = mCalculationTable[right];
            // get number's index
            int index = new_token.section("",1).toInt();
            // get the number operand
            QPair<QString*,Number*> pair = mNumberOperands.at(index);
            Number* number = pair.second;
            right_ptr = reinterpret_cast<Operand*>(number);
        }
        operator_str.replace(right,new_token);
    }
    else
    {
        right_ptr = getOperandObj(right);
    }

    if(!mCalculationTable.contains(operator_str))
    {
        new_token = ("O" + QString::number(mOperatorOperands.size()));
        QString* ptr = new QString(operator_str);
        int operation_number = -1;
        int op_index = operator_str.indexOf("^",0);
        QString op_str(operator_str.section("",op_index+1, op_index +3));
        Operator* operator_ptr(
                    new Operator(InFixInterpret::
                                DecodeOperation(op_str,operation_number),
                                                right_ptr,left_ptr));
        QPair<QString*,Operator*> pair;
        pair.first = ptr;
        pair.second = operator_ptr;
        mOperatorOperands.append(pair);
        mCalculationTable.insert(operator_str,new_token);
    }
    else
    {
        new_token = mCalculationTable[operator_str];
    }
    return new_token;
}



QString CalculationFlyWeight::addFunction(QString function_str,
                                          const QStringList &parameters)
{
    // Setup values for parsing
    int param_count(parameters.size());
    QString current_param;
    QList<Operand*> param_ptrs;
    QString new_token;
    // find each parameter and check their validity
    for(int i = 0; i < param_count; ++i )
    {
        current_param = parameters.at(i); // get current parameter
        if(current_param[0].isDigit() || current_param[0] == '-')
        {   // check if not already in mCalculationTable
            if(!mCalculationTable.contains(current_param))
            {
                // Create new value Number, not possible for any other type
                // to make it to function stage, would have been processed
                // already

                // Create Number Token
                new_token = ("N" + QString::number(mNumberOperands.size()));
                // Create new Number Data Value string
                QString* ptr = new QString(current_param);
                // and Number pointer
                Number* num_ptr =new Number(ptr);

                // now create the pair and fill it
                QPair<QString*,Number*> pair;
                pair.first = ptr;
                pair.second = num_ptr;

                // put the created pair on the rear of operands
                // at the encoded token index
                mNumberOperands.append(pair);
                // insert the string value and its matching token to flyweight
                // main storage
                mCalculationTable.insert(current_param,new_token);
                // attach to param pointer for Function creation
                param_ptrs.append(num_ptr);
            }
            else
            {
                // else, grab the number value from flyweight
                // get number's index
                new_token = mCalculationTable[current_param];
                int index = new_token.section("",1).toInt();

                // get the number operand
                QPair<QString*,Number*> pair = mNumberOperands.at(index);
                Number* number(pair.second);
                param_ptrs.append(number);
            }
            // remove the current_param and replace with token
            function_str.replace(current_param,new_token);
        }
        else
        {
            // Else it is a more complex Operand (operator,variable,function)
            Operand* ptr = getOperandObj(current_param);
            // attach to param_ptrs
            param_ptrs.append(ptr);
        }
    }

    // check if need to create new function
    if(!mCalculationTable.contains(function_str))
    {
        new_token = ("F" + QString::number(mFunctionOperands.size()));
        QString* ptr = new QString(function_str);
        int func_number = -1;
        Function* func_ptr(new Function(InFixInterpret::DecodeOperation(
                                        function_str.section("",0,
                                        function_str.indexOf("(")),
                                        func_number),param_ptrs));
        //
        QPair<QString*,Function*> pair;
        pair.first = ptr;
        pair.second = func_ptr;
        mFunctionOperands.append(pair);
        mCalculationTable.insert(function_str,new_token);
    }
    else
    {
        // check if in the system or no
        new_token = mCalculationTable[function_str];
    }
    return new_token;
}



Operand* CalculationFlyWeight::getOperandObj(QString token)
{

    Operand* return_obj;// place to store string
    // find the number section; token = F215, index = 215
    int operand_index = token.section("",1).toInt();
    //find pair, then return pair.second after reinterpret cast
    switch(token.at(0).toLatin1())
    {
        // if function, cast to operand store in return_obj
        case 'F' : { QPair<QString*,Function*> pair =
                     mFunctionOperands.at(operand_index);
                     return_obj = reinterpret_cast<Operand*>(pair.second);
                     break;}
        // if number, cast to operand store in return_obj
        case 'N' : { QPair<QString*,Number*> pair =
                     mNumberOperands.at(operand_index);
                     return_obj = reinterpret_cast<Operand*>(pair.second);
                     break;}
        // if operator, cast to operand store in return_obj
        case 'O' : { QPair<QString*,Operator*> pair =
                     mOperatorOperands.at(operand_index);
                     return_obj = reinterpret_cast<Operand*>(pair.second);
                     break;}
        // if variable, cast to operand store in return_obj
        case 'V' : { return_obj = mVariableOperands.at(operand_index);
                     break;}
        default  : {return_obj = nullptr; break;} // else return null
    }
     return return_obj; // exit with return_obj
}

QString CalculationFlyWeight::getOperandStr(QString token)
{
    // find the number section; token = F215, index = 215
    int operand_index = token.section("",1).toInt();// number - Char @ index 0
    QString return_obj; // place to store string
    //find pair, then return pair.first
    switch(token[1].toLatin1())
    {
        // If type is function look in mFunctionOperands
        case 'F' : { QPair<QString*,Function*> pair =
                     mFunctionOperands.at(operand_index);
                     return_obj = *pair.first; // set the return string
                     break;}
        // if type is Number look in the mNumberOperands
        case 'N' : { QPair<QString*,Number*> pair =
                     mNumberOperands.at(operand_index);
                     return_obj = *pair.first; // set the return string
                     break;}
        // if type is Number look in the mNumberOperands
        case 'O' : { QPair<QString*,Operator*> pair =
                     mOperatorOperands.at(operand_index);
                     return_obj = *pair.first;// set the return string
                     break;}
        // if type is Number look in the mNumberOperands
        case 'V' : { Var* var = mVariableOperands.at(operand_index);
                     return_obj = var->mName; // set the return string
                     break;}
       default  : {return_obj = QString(); break;} // return blank
    }
    return return_obj; // return found string
}


// Clears all Calculation memory created during runtime
CalculationFlyWeight::~CalculationFlyWeight()
{
    // find the size of Variables container
    int size = mVariableOperands.size();
    for(int i(0); i< size; ++i)
    {
        // delete each variable
        delete mVariableOperands[i];
    }
    mVariableOperands.clear(); // clear Variables

    // Delete Operators
    size =mOperatorOperands.size();
    for(int i(0); i < size; ++i)
    {
        // find each pair
        QPair<QString*, Operator*> pair = mOperatorOperands.at(i);
        delete pair.first; // delete the QString* operation
        delete pair.second; // delete the Operator* used for b-expression tree
    }
    mOperatorOperands.clear(); // clear operators

    // Delete Functions
    size =mFunctionOperands.size();
    for(int i(0); i < size; ++i)
    {
        // find each pair
        QPair<QString*, Function*> pair = mFunctionOperands.at(i);
        delete pair.first; // delete the QString* function text
        delete pair.second;// delte the Function* used for b-expression tree
    }
    mFunctionOperands.clear(); // clear functions

    // Delete Numbers
    size = mNumberOperands.size();
    for(int i(0); i < size; ++i)
    {
        // find each pair data
        QPair<QString*, Number*> pair = mNumberOperands.at(i);
        delete pair.first;// delete the QString* mValue
        delete pair.second;// delete the Number* used for b-expression tree
    }
    mNumberOperands.clear(); // clear operands
}
