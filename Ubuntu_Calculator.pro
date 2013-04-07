
# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

QMAKE_CXXFLAGS += -std=c++0x

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Backend/Mediator/eventhandler.cpp \
    Backend/Composite/variable.cpp \
    Backend/Composite/operator.cpp \
    Backend/Composite/operand.cpp \
    Backend/Composite/number.cpp \
    Backend/Composite/function.cpp \
    Backend/Composite/equation.cpp \
    Backend/Flyweight/calculationflyweight.cpp \
    Backend/Interpreter/infixinterpret.cpp \
    Backend/Proxy/variableproxy.cpp \
    Backend/Proxy/equationproxy.cpp

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    Backend/Mediator/eventhandler.hpp \
    Backend/Composite/variable.hpp \
    Backend/Composite/operator.hpp \
    Backend/Composite/operand.hpp \
    Backend/Composite/number.hpp \
    Backend/Composite/function.hpp \
    Backend/Composite/equation.hpp \
    Backend/Flyweight/calculationflyweight.hpp \
    Backend/Globals/globals.hpp \
    Backend/Globals/exceptions.hpp \
    Backend/Interpreter/infixinterpret.hpp \
    Backend/Proxy/variableproxy.hpp \
    Backend/Proxy/ivariableproxy.hpp \
    Backend/Proxy/iequation.hpp \
    Backend/Proxy/equationproxy.hpp

OTHER_FILES += \
    User_Interface/qml/NumberDisplay.qml \
    User_Interface/qml/main.qml \
    User_Interface/qml/CurrentFunction.qml \
    User_Interface/qml/Button.qml \
    User_Interface/qml/Variable.qml \
    User_Interface/qml/VarNameBar.qml \
    User_Interface/qml/Operations_Button/Operation.qml \
    User_Interface/qml/Operations_Button/OperationTab.qml \
    User_Interface/qml/ClearTab.qml \
    User_Interface/qml/TabItem.qml

RESOURCES += \
    User_Interface/resources.qrc
