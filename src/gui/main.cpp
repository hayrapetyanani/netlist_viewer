#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "../database/port.hpp"
#include "../database/project.hpp"
#include <tcl.h>
#include <assert.h>

void addNet(Project* proj, const std::string& name, Instance* inst1, Instance* inst2)
{
    InstancePort* outPort = inst1->addPort("out", Port::out);
    InstancePort* inPort = inst2->addPort("in", Port::in);
    proj->addNet(name, inPort, outPort);
}


void addModules()
{
    Project* proj = Project::get();
    Module* module1 = proj->addModule("module1");
    Module* module2 = proj->addModule("module2");
    Module* module3 = proj->addModule("module3");

    Instance* inst2 = module1->addInstance("inst2", module2);
    Instance* inst1 = module2->addInstance("inst1", module1);
    Instance* inst3 = module2->addInstance("inst3", module1);
    Instance* inst4 = module3->addInstance("inst4", module2);
    addNet(proj, "net1", inst1, inst2);
    addNet(proj, "net2", inst3, inst2);
    addNet(proj, "net3", inst3, inst4);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    addModules();
    MainWindow w;
    w.show();
    return a.exec();
}
