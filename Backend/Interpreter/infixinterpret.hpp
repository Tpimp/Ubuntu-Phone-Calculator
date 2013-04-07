#ifndef INFIXINTERPRET_HPP
#define INFIXINTERPRET_HPP

#include <QString>
#include "../Backend/Globals/globals.hpp"
#include <QRegExp>


//Define simple operators and input grammar
static const char Plus = '+',
Subtract = '-',
Divide = '/',
Multiply = '*',
Negate = 'n',
Comma = ',',
Paren_Left = '(',
Paren_Right = ')';

// DEFINE Tokenized Identifiers
static const char Variable = 'V',
           LocalFunction = 'F',
           Stored = 'S',
           Op = 'O';


//Define Complex Operand types
static const char* FUNCS[] = {"ABS","MIN","MAX"};
static const int FUNCS_COUNT = 3;



//TODO replace with Qt5.0 QRegularExpression <- 4x the performance.
// Define Regular Expression
static const QRegExp OPERAND_EXPRESSION
      ("[\\(?;?\\^?]?(-?\\w?\\d{1,}.?\\d{0,})[;\\)$\\^]");
 //OPERAND EXPRESSION in human terms
 /*****************************************************************************
 * First_Char: is ONE or ZERO ( ? ; or ^  "[\\(?;?\\^?]?" // one must exist
 * Begin_Capture: "(" signifies to Capture digits until ")", see QRegExp docs
 * Negative:ONE or ZERO (-) (negative signs) "-?"
 * ONE OR ZERO Letters  "\\w?" //If tokenized operand
 * Fourth_Char-**: ONE Digit string through X number of digits 0-9 "\\d{1,}"
 * End_Digits: ONE or ZERO '.' -if decimal place   ".?"
 * StringDigits_Fraction**: ZERO or more digits 0-9 (fraction) "\\d{0,}"
 * End_Capture: ")" don't capture next chars but do match them
 * Match_End: Look for ';' (func param), ')' '^' '$' (NULL, end of string)
 * Matches: "N34", "(V6)", "-32432.94293", "324.32432" "^*^34^/^" <-grabs 35
 *****************************************************************************/
static const QRegExp OPERATOR_EXPRESSION("(\\^[\\*\\+-/]?\\^)");
 //OPERATOR EXPRESSION in human terms
/*****************************************************************************
* First Char: literal '^'
* Second Char: One of *,+,-,/
* Final Char: literal '^'
*****************************************************************************/

// check if a string countatins all digits or digits and a decimal
static bool STR_IS_NUMBER(const QString& string)
{
    int size = string.size();
    int decimal_count(0);
    bool return_val = true;
    // if first character is not a digit or negative sign
    if(!(string[0].isDigit() || string[0].toLatin1() == '-'))
    {
        return false;
    }
    for(int i = 1; i < size; ++i) // for each character
    {
        if(!string[i].isDigit()) // if it is not a digit
        {
            if(string[i].toLatin1() == '.' && (decimal_count == 0))
            {
                decimal_count++; // if its the first decimal
            }
            else
            {
                return_val = false; // else too many decimals to be a number
                break;
            }
        }

    }
    return return_val; // return is a number or not
}

// checks if ^*^,^/^,^+^,^-^, matches current precedence level
static bool MATCHES_PRECEDENCE_LEVEL(const QString str,int precedence_level)
{
    bool return_val = false;
    if(str[0].toLatin1() == 'O') // if Tokenized already, skip
        return false;
    else
    {
        if(precedence_level >0) // if looking to match * or /
        {
            if(str.contains('*') || str.contains('/'))
            {
                return_val == true; // if found true
            }// else false will be returned from above
        }
        else
        {
           return_val == true; // else if its +/- precedence doesn't matter
        }
     }
     return false; // else return false
}

static bool CheckFunctionParameterCount(int count, QString function_name)
{
    return true; //eventually walk down and match known parameter counts
}


class Operand;
class CalculationFlyWeight;

class InFixInterpret
{


protected:


    //create compare strings for functions

    friend class CalculationFlyWeight;
    InFixInterpret();
    int OperatorPrecedence(Expression operator_type);
    static void ProcessNumbers(CalculationFlyWeight &flyweight,
                                 QString & expression);
    static void ProcessOperators(CalculationFlyWeight &flyweight,
                                 QString & expression);
    static void ProcessFunction(CalculationFlyWeight &flyweight,
                                 QString& expression);
  //  static void Decode_Operator_Precedence(
  //          CalculationFlyWeight &flyweight, QStringList& operands,
  //                      QStringList& operators, QString& expression);
    static Expression DecodeOperation(QString operator_str, int &func_number);

public:
    static QString  Evaluate(QString expression, CalculationFlyWeight &flyweight);

};

#endif // INFIXINTERPRET_HPP
