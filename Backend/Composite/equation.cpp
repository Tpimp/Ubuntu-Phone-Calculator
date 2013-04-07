#include "equation.hpp"

Equation::Equation(CalculationFlyWeight &flyweight, QString &name, QString &user_string, Operand *root) :
    Var(flyweight,name,user_string,root)
{}


void Equation::addOperand(Operand *operand,Operator* operation)
{

    if(mRoot) // if root
    {
        Operator*& root = reinterpret_cast<Operator*&>(mRoot);
        Operator*& target = findTarget(root);
        if( *operation < *target) // if target is * and operation is +/-
        {
            target->mRight = operand; //target operation takes the operand
            operation->mLeft = root; // root becomes new operand (result)
            mRoot = operation; // new operation becomes root
        }
        else if( *operation == *target) // if they are equal
        {
            if(root != target) // if the target is not root
            {
                target->mRight = operand; // operand goes on the right
                operation->mLeft = root->mRight; // insert operation
                root->mRight = operation; //operation becomes root's right op
            }
            else // else root is the target
            {
                target->mRight = operation; // perform operation first
                operation->mLeft = operand; // operation keeps operand
            }
        }
        else // else if target has least precedence
        {
            target->mRight = operation; // perform operation first
            operation->mLeft = operand; // operation keeps operand
        }
    }
    else // else first operator, add to root then assign left operand
    {
        mRoot = operation;
        operation->mLeft = operand;
    }
}


void Equation::clearEquation()
{
    mRoot = nullptr;
}



Operator*& Equation::findTarget(Operator *&op)
{
    // find furthest right child with not right child
    if(op)
    {
        Operator* current = op;
        Operator* prev(nullptr);
        while(current->mRight) // while current->mRight is not null
        {
            prev = current;
            current = reinterpret_cast<Operator*>(current->mRight);
        }
        if(prev)
        {
            return reinterpret_cast<Operator*&>((*prev).mRight);
        }
        else
            return op;
    }
    return op;
}

void Equation::removeRearItem()
{
    // to be fixed
    if(mRoot)
    {
        //mLastNode->mRight = nullptr;
    }
}

Equation::~Equation()
{
    mRoot = nullptr;
}
