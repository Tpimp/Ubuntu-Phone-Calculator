#ifndef CALCULATIONFLYWEIGHT_HPP
#define CALCULATIONFLYWEIGHT_HPP
#include <QHash>
#include <QVarLengthArray>
#include <QString>
#include <QStringList>
#include <QPair>
#include "../Backend/Globals/globals.hpp"

class Operand;
class Number;
class Function;
class Operator;
class Var;


class CalculationFlyWeight
{

    protected:
        friend class InFixInterpret;


        // mCalculationTable<key,value>
        // mCalculationTable<real_calcualtion_str, tokenized_string>
        QHash<QString,QString> mCalculationTable; // master string table

        // tokenized number,function,operator, and variable operands
        QVarLengthArray<QPair<QString*,Number*> > mNumberOperands;// N*
        QVarLengthArray<QPair<QString*,Function*> > mFunctionOperands;// F*
        QVarLengthArray<QPair<QString*,Operator*> > mOperatorOperands;// O*
        QVarLengthArray<Var*> mVariableOperands;// V*
        // internal member functions used by interpreter to request type creation
        QString addFunction(QString function_str, const QStringList &parameters);
        QString addOperator(QString operator_str, QString left, QString right);
        QString addNumber(QString value);

    public:
        CalculationFlyWeight();
        QString insertCalculation(QString calculation,QString name, Var*& previous);

        //QString getToken(QString calculation);
        QString getOperandStr(QString token);
        //QString variableToStr(Variable* var);
        Operand* getOperandObj(QString token);
        ~CalculationFlyWeight();

};

#endif // CALCULATIONFLYWEIGHT_HPP
