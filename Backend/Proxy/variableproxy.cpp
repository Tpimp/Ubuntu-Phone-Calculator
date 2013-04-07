#include "variableproxy.hpp"

//NOTHING Fancy, call all the methods of the attached proxy method
// IF there is currently an variable attached

VariableProxy::VariableProxy() :
    mAttachedVariable(nullptr)
{
}

void VariableProxy::attachProxy(Var* to_be_attached)
{
    mAttachedVariable = to_be_attached;
}

void VariableProxy::detachCurrentProxy()
{
    mAttachedVariable = nullptr;
}

void VariableProxy::setEquation(QString new_equ)
{
    if(mAttachedVariable)
        mAttachedVariable->setEquation(new_equ);
}


void VariableProxy::setName(QString new_name)
{
    if(mAttachedVariable)
        mAttachedVariable->setName(new_name);
}

void VariableProxy::setRoot(Operand *new_root)
{
    if(mAttachedVariable)
        mAttachedVariable->setRoot(new_root);
}


VariableProxy::~VariableProxy()
{
    mAttachedVariable = nullptr;
}
