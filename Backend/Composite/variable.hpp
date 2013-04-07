#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include "operand.hpp"
#include "../Backend/Proxy/ivariableproxy.hpp"
#include <QString>
#include <QList>
class CalculationFlyWeight;

class Var : public Operand, iVariableProxy
{
    protected:
        friend class InFixInterpret;
        friend class CalculationFlyWeight;
        Operand* mRoot;
        CalculationFlyWeight& mFlyWeight;
        QString mName;
        QString mUserString;
        ~Var();
    public:
    Var(CalculationFlyWeight& flyweight,QString& name,
        QString& user_string, Operand* root = nullptr);
    QString getEquation(){return mUserString;}
    QString getName(){return mName;}
    void setEquation(QString new_equ);
    void setName(QString new_name);
    void setRoot(Operand* new_root);
    virtual QString Solve();
};
#endif // VARIABLE_HPP
