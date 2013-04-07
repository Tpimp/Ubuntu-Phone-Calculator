#include "infixinterpret.hpp"
#include <QStringList>
#include <QRegExp>
#include "../Backend/Globals/exceptions.hpp"
#include "../Backend/Flyweight/calculationflyweight.hpp"
InFixInterpret::InFixInterpret()
{
}

// CONVERT STRING TO FUNCTION
Expression InFixInterpret::DecodeOperation(QString operator_str, int& func_number)
{
    Expression return_val = NUMBER;
    if(operator_str.at(0) == '^')
    {
        // switch on the type of character
        switch (operator_str.at(1).toLatin1())
        {
            //compare using static const chars, defined in infixinterpret.hpp
            case Plus: {return_val = PLUS; break;}
            case Subtract: {return_val = SUBTRACT; break;}
            case Divide : {return_val = DIVIDE; break;}
            case Multiply : {return_val = MULTIPLY; break;}
            case Negate : {return_val = NEGATE; break;}
            default : {return_val = NUMBER; break;}
        }
    }
    else// else its a function
    {
        // decode what type of function
        if(!operator_str.at(1).isLetter()) // if second character is digit
        {
            //  Decode what Type of Function
            //  Switch on FUNCTION TOKEN
            switch  (operator_str.at(0).toLatin1())
            {
                case LocalFunction : {return_val = LOCAL; break;}
                case Op : {return_val = OPERATOR; break;}
                case Stored : {return_val = STORED; break;}
                case Variable : {return_val = VARIABLE; break;}
                default :  {return_val = LOCAL; break;}
            }
            func_number = operator_str.section("",1,operator_str.indexOf("]")-1).toInt();
        }
        else // else its a a non-tokenized Function, look in known FUNCS
        {
            // KNOWN as in hard coded into the infixinterpreter. see infixinterpret.hpp
            for(int i = 0; i < FUNCS_COUNT; i++)
            {
                if(operator_str.compare(QString(FUNCS[i])) == 0)
                {
                    return_val = Expression(ABSOLUTE+i);
                    break;
                }
            }
            //if(return_val == NUMBER) // Function not found
        }        // return_val = CheckUserFunctions(operator_str,func_number)
    }
    return return_val;
}


void InFixInterpret::ProcessFunction(CalculationFlyWeight& flyweight, QString& expression)
{
    // create a list to store operands into
    QStringList operands;
    int position(0); // start at front of string

    // find each Operand
    while((position = OPERAND_EXPRESSION.indexIn(expression,position)) >= 0)
    {
        operands << OPERAND_EXPRESSION.cap(1);      // store it
        position+= OPERAND_EXPRESSION.matchedLength();// increment to next
    }
    // create the function token and add the function to the flyweight
    expression = flyweight.addFunction(expression,operands);
    // simultaneously updates expression on the outside (QString&)
}


void InFixInterpret::ProcessNumbers(CalculationFlyWeight &flyweight, QString &expression)
{
    //TODO SHOW TOP Process Numbers
    QStringList parameters; // create stringlist to store operands in
    int position(0);
    // while still finding occurences of OPERAND_EXPRESSION in expression
    while((position = OPERAND_EXPRESSION.indexIn(expression,position)) >= 0)
    {
        parameters << OPERAND_EXPRESSION.cap(1).remove(")").remove("^");      // store it
        position+= OPERAND_EXPRESSION.matchedLength();// increment to next
    }
    QString token; // to store temporary tokens in
    foreach(const QString& number,parameters) //for each number in stringlist
    {
        if(STR_IS_NUMBER(number)) // to check if a valid number
        {
            token = flyweight.addNumber(number); //get token add to hash
            expression.replace(number,token);  // replace in string
        }
    }
}


void InFixInterpret::ProcessOperators(CalculationFlyWeight& flyweight,QString& expression)
{
    //TODO Show Top level process operators
    QStringList operands;
    QStringList operators;
    QString token;
    QString left;
    QString right;
    int position(0);
    //create operand list
    while((position = OPERAND_EXPRESSION.indexIn(expression,position)) >= 0)
    {
        operands << OPERAND_EXPRESSION.cap(1);        // store it
        position+= OPERAND_EXPRESSION.matchedLength();// increment to next
    }
    if(operands.size()< 2) // if not found two operands, missed the ending item
    {
        operands << expression.section("",expression.lastIndexOf("^")+2);
    }
    position = 0;
    // while still finding pattern matches
    while((position = OPERATOR_EXPRESSION.indexIn(expression,position)) >= 0)
    {
        operators << OPERATOR_EXPRESSION.cap(1);       // store it
        position+= OPERATOR_EXPRESSION.matchedLength();// increment to next
    }
    // finished finding operators, now parse by precedence
    for(int i(0); i < operators.size();)
    {
        if(MATCHES_PRECEDENCE_LEVEL(operators[i],1))// if * or /
        {
            // grab the two operands off the corresponding list
            right = operands.at(i+1);
            left = operands.at(i);
            // create the operation str
            QString op_str = (left + operators[i] + right);
            // add the operator and
            token = flyweight.addOperator(op_str,left,right);
            // replace with tokenized string
            expression.replace(op_str,token);
            // now put the token in for the left_operand
            operands[i] = token;
            // remove the operator and
            operands.removeAt(i+1);
            operators.removeAt(i);
        }
        else
        {
            ++i; // else skip it
        }
    }
    while(!operators.isEmpty()) // if + and - left,
    {
        // grab the items off the front
        right = operands.at(1);
        left = operands.at(0);
        // build the operator string
        QString op_str = (left + operators[0] + right);
        // add operator
        token = flyweight.addOperator(op_str,left,right);
        // replace the string with token
        expression.replace(op_str,token);
        operands[0] = token; // replace left operand with
        operands.removeAt(1); // pop them both off
        operators.removeAt(0);
    }
}

QString InFixInterpret::Evaluate(QString expression, CalculationFlyWeight &flyweight)
{
    // Check if all parentheses have matching end parentheses
    // starting at the rear + one (will be converted to second from last)
    int left_pos(expression.size()+1);

    // create search index and string processing temporary values
    int right_pos(0);
    int search_index(0);
    int end(0);
    QString new_expression;
    QString substring;

    // process parens first
    while(expression.contains("("))
    {
        // Find the next set of ()
        left_pos = expression.lastIndexOf("(",left_pos-2)+1;
        right_pos = expression.indexOf(")",left_pos+1)+1;

        // grab that sub expression from expression
        substring = (expression.section("",left_pos,right_pos));

        // store a copy in new_expression
        new_expression= substring;

        // process the Number values within the sub_expression (Number.hpp)
        ProcessNumbers(flyweight,new_expression);

        // new_expression is now tokenized, sub_expression within expression
        expression.replace(substring,new_expression); // to the tokenized str
        substring = new_expression; // set substring to current tokenized str

        // Process the operations in the sub_expression
        ProcessOperators(flyweight,new_expression);
        // new_expression is now tokenized
        expression.replace(substring,new_expression); // replace w/ tokenized

        // Check if the current set of parens belong to a function
        // i.e MAX(02;N3), but up until now (02;N3) has been being processed
        //
        search_index = (left_pos-2); // find left paren -1
        end = search_index; // set both values on "last" char, if exists
        // while still finding a letter and now past 0 index
        while(search_index >=0 && expression[search_index].isLetter())
        {  search_index--; } // decrement

        // Functions must be 3 letters or longer
        if((end - search_index) <3) // check if found 3 or more letters
        {
            // if not, remove the current set of parens
            substring =new_expression;
            substring.remove(")");
            substring.remove("(");
            // replace the current "(new_expression)" with "new_expression"
            expression.replace(new_expression,substring);
        }
        else
        {
            // found function- decode!
            // find right paren
            int closing = expression.indexOf(")",search_index+2);
            // get the WHOLE function for replace later
            QString func_str(expression.section("",search_index+2,closing+1));
            substring = func_str; // make copy
            // Process the function into a tokenized function
            ProcessFunction(flyweight,func_str);
            // replace literal function with tokenized F*
            expression.replace(substring,func_str);
        }

    }

    // all Parens are processed, look for top level operations and Numbers
    // get substring
    substring = (expression.section("",0,expression.size()));
    // process numbers
    ProcessNumbers(flyweight,substring);
    // process operators
    ProcessOperators(flyweight,substring);
    // return tokenized O*
    expression=substring;

   return expression;
}


