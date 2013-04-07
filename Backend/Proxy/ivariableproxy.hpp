#ifndef IVARIABLEPROXY_HPP
#define IVARIABLEPROXY_HPP

#include <QString>
#include "../Backend/Composite/operand.hpp"
class iVariableProxy
{
    // Define the public interface methods for the Variable proxy
    public:
    virtual void setName(QString new_name) = 0;
    virtual void setEquation(QString new_equ) = 0;
    virtual void setRoot(Operand* new_root) = 0;
};

#endif // IVARIABLEPROXY_HPP
