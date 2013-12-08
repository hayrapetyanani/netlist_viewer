#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "../database/port.hpp"
#include "../database/project.hpp"
#include <tcl.h>
#include <assert.h>

Net getNet()
{
        Port inPort("in", Port::in);
        Port outPort("out", Port::out);
        Net net("net1", &inPort, &outPort);
        return net;
}


void addModules()
{
    Project* proj = Project::get();
    Module* module1 = proj->addModule("module1");
    Module* module2 = proj->addModule("module2");

    module2->addInstance("inst1", module1);
    module2->addNet(getNet());
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    addModules();
    MainWindow w;
    w.show();
    return a.exec();
}
