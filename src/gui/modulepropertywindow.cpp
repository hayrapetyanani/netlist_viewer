#include <iostream>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "modulepropertywindow.h"

ModulePropertyDialog::ModulePropertyDialog(QWidget* parent, Module* modl) : QDialog(parent)
{
    module = modl;
    portNameEdit = NULL;
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    
    nameLabel = new QLabel("Module Name");
    if (module != NULL) 
        nameEdit = new QLineEdit(module->name().c_str());
    else
	nameEdit = new QLineEdit("");
    nameLabel->setBuddy(nameEdit);
   
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    
    mainLayout->addLayout(nameLayout);
    
    saveButton = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");

    connect(cancelButton, SIGNAL(clicked()),this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()),this, SLOT(saveData()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    
    QVBoxLayout *portsLayout = new QVBoxLayout;
    QLabel* portsLabel = new QLabel("Ports");
    portsLayout->addWidget(portsLabel);
    if (module != NULL)
    {	
    	Module::PortCollection ports = module->ports();
	foreach (Port p, ports) {
		QHBoxLayout *portNameLayout = new QHBoxLayout;
		if (p.type() == Port::in) 
		{
			QLabel* inLabel = new QLabel("In Port: ");				
			QLabel* port = new QLabel(p.name().c_str());
			portNameLayout->addWidget(inLabel);
			portNameLayout->addWidget(port);
		}
		else 
		{
			QLabel* inLabel = new QLabel("Out Port: ");				
			QLabel* port = new QLabel(p.name().c_str());
			portNameLayout->addWidget(inLabel);
			portNameLayout->addWidget(port);
		}
        
        	portsLayout->addLayout(portNameLayout);
    	}
	mainLayout->addLayout(portsLayout);
    }
    else 
    {
	QHBoxLayout* portNameLayout = new QHBoxLayout;
	QLabel* portNameLabel = new QLabel("Port Name");
	portNameEdit = new QLineEdit("");
	portNameLayout->addWidget(portNameLabel);
	portNameLayout->addWidget(portNameEdit);
        mainLayout->addLayout(portNameLayout);	
    }		

    QVBoxLayout *netsLayout = new QVBoxLayout;
    QLabel* netsLabel = new QLabel("Nets");
    netsLayout->addWidget(netsLabel);
    
    if (module != NULL)
    {	
	Module::NetCollection nets = module->nets();
	    foreach (Net n, nets) {
        	QLabel* netName = new QLabel(n.name().c_str());
	        netsLayout->addWidget(netName);
    	}
	mainLayout->addLayout(netsLayout);
    }	
    
    
    
    
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle("Module Properties");
}

void
ModulePropertyDialog::saveData()
{
	if (portNameEdit == NULL)
	{
		QString name = nameEdit->text();
    
		std::string moduleName = nameEdit->text().toUtf8().constData();
    		Project* proj = Project::get();
		if (!proj->checkIfModuleExists(moduleName))
			module->setName(moduleName);
	}
	else
	{
		QString name = nameEdit->text();
		
		std::string moduleName = nameEdit->text().toUtf8().constData();
		Project* proj = Project::get();
		if (!proj->checkIfModuleExists(moduleName))
		{
			//proj->addModule(moduleName);
		}
	}
	close();
}
