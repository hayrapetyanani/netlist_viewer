#include <iostream>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "propertywindow.h"
#include "../database/project.hpp"

PropertyDialog::PropertyDialog(QWidget* parent, Instance* inst) : QDialog(parent)
{
    instance = inst;

    nameLabel = new QLabel("Instance Name");
    nameEdit = new QLineEdit(instance->name().c_str());
    nameLabel->setBuddy(nameEdit);

    masterNameLabel = new QLabel("Master Name");
    const Module* masterModule = instance->masterModule();
    masterNameEdit = new QLabel(masterModule->name().c_str());
    masterNameLabel->setBuddy(masterNameEdit);

    parentNameLabel = new QLabel("Parent Name");
    Module* parentModule = instance->parentModule();
    parentNameEdit = new QLineEdit(parentModule->name().c_str());
    parentNameLabel->setBuddy(parentNameEdit);

    saveButton = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");

    connect(cancelButton, SIGNAL(clicked()),this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()),this, SLOT(saveData()));


    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);

    QHBoxLayout *masterNameLayout = new QHBoxLayout;
    masterNameLayout->addWidget(masterNameLabel);
    masterNameLayout->addWidget(masterNameEdit);


    QHBoxLayout *parentNameLayout = new QHBoxLayout;
    parentNameLayout->addWidget(parentNameLabel);
    parentNameLayout->addWidget(parentNameEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(masterNameLayout);
    mainLayout->addLayout(parentNameLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle("Instance Properties");
}

void
PropertyDialog::saveData()
{
    instanceName = nameEdit->text().toUtf8().constData();
    instance->setName(instanceName);

    Project* proj = Project::get();
    std::string parentName = parentNameEdit->text().toUtf8().constData();
    Module* parentModule = instance->parentModule();
    if (parentName != parentModule->name())
    {
	Module* newParentModule = proj->getModuleByName(parentName);
	if (newParentModule != NULL)
	{
		parentModule->removeInstance(instanceName);
		instance->setParentModule(newParentModule);
		newParentModule->addInstance(instance);
	}
    }	
    close();
}
