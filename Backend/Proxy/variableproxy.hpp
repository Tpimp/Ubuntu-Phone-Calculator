#ifndef VARIABLEPROXY_HPP
#define VARIABLEPROXY_HPP

#include "ivariableproxy.hpp"
#include "../Backend/Composite/operand.hpp"
#include "../Backend/Composite/variable.hpp"
//*****************************************************************************
// VariableProxy "attaches" to a variable and then utilizes its methods.
// When necessary the variable will be detached from the proxy and then another
// variable will be attached in it's place.The variable currently attached will
// be represented in the variable display (see NumberDisplay.qml)
//******************************************************************************
class VariableProxy : public iVariableProxy
{
    protected:
        //current Delegate
        Var * mAttachedVariable;
    public:
        VariableProxy();
        // proxy management
        void attachProxy(Var* to_be_attached);
        Operand* getAttachedVar(){return reinterpret_cast<Operand*>(mAttachedVariable);}
        void detachCurrentProxy();
        // proxy interface methods
        void setEquation(QString new_equ);
        void setName(QString new_name);
        void setRoot(Operand *new_root);
        ~VariableProxy();
};

#endif // VARIABLEPROXY_HPP
