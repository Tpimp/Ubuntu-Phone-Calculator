#include "variable.hpp"
#include "../Backend/Flyweight/calculationflyweight.hpp"
#include <QDebug>
Var::Var(CalculationFlyWeight &flyweight, QString &name, QString &user_string, Operand* root)
    // store the data members and set type variable
    :Operand(VARIABLE),mFlyWeight(flyweight), mRoot(root), mName(name), mUserString(user_string)
{
    qDebug() << "Creating variable with name" << name;
}

// Proxy Methods
void Var::setEquation(QString new_equ)
{
    Var* new_var(this);
    mFlyWeight.insertCalculation(new_equ,mName,new_var);
}

void Var::setName(QString new_name)
{
    Var* new_var(this);
    mFlyWeight.insertCalculation(mUserString,new_name,new_var);
}

void Var::setRoot(Operand* new_root)
{
    mRoot = new_root;
}


// Chain of Responsibility, DISPATCHER-> always passes responsibility.
QString Var::Solve()
{
    return mRoot->Solve(); // Chain of responsibility
}


Var::~Var()
{
    // clear data values
    mRoot = nullptr;
    mName = "";
    mUserString = "";
}
