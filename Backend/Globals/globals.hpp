#ifndef GLOBALS_HPP
#define GLOBALS_HPP


enum Expression
{
    // Define basic type number
    NUMBER =0,
    // Define Operators
    PLUS,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    NEGATE,
    // Define Known Functions
    ABSOLUTE,
    MIN,
    MAX,
    // Define Character types
    COMMA,
    PAREN_LEFT,
    PAREN_RIGHT,
    LOCAL,
    OPERATOR,
    STORED,
    VARIABLE,
    EQUATION,
    USER_DEFINED_FUNCTION // starting point for user defined functions
    // User defined functions will be loaded from
    // Local FileSystem/User Settings File or Flash Memory
};




#endif // GLOBALS_HPP
