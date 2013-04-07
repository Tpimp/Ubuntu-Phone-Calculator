#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "Backend/Mediator/eventhandler.hpp"
#include "Backend/Flyweight/calculationflyweight.hpp"
#include <QQmlEngine>
#include <QVariant>
#include <QDebug>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv); // Create the base application class

    QtQuick2ApplicationViewer viewer; // create the QML viewer window



    // The below code will eventually be wrapped in a top level class
    // Initialize the flyweight
    //Create first Variable "A"
    Var* current_var(nullptr);
    CalculationFlyWeight flyweight;
    QString token(flyweight.insertCalculation("0","A",current_var));

    // Initialize the InputEventHandle class connects QML user input -> C++ Backend logic
    InputEventHandler in(&flyweight,viewer.engine()->rootContext(),&viewer,nullptr,current_var);

    // Make the Event Handler visible as QObject& in QML
    viewer.engine()->rootContext()->setContextProperty("EventHandler",&in);

    // simulate a user input call to place A as the current variable in the editor
     in.requestVariable(token);
    // set the main qml file

    viewer.setMainQmlFile(QStringLiteral("User_Interface/qml/main.qml"));
    viewer.showExpanded(); // set fullscreen, and visible
    return app.exec(); // run the main Application Event loop
}
