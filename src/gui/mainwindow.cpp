#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../database/module.hpp"
#include "../database/project.hpp"
#include <tcl.h>
#include <propertywindow.h>
#include <modulepropertywindow.h>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    tcl_interp_ = Tcl_CreateInterp();
    ui->setupUi(this);
    initializeTreeView();
    QObject::connect(ui->executeButton, SIGNAL(clicked()), this, SLOT(executeTclCommand()));
}

void MainWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
    //get the text of the selected item
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString selectedText = index.data(Qt::DisplayRole).toString();
    //find out the hierarchy level of the selected item
    int hierarchyLevel=1;
    QModelIndex seekRoot = index;
    while(seekRoot.parent() != QModelIndex())
    {
        seekRoot = seekRoot.parent();
        hierarchyLevel++;
    }
    Project* proj = Project::get();
    Project::ModuleCollection modules = proj->getModules();
    if (hierarchyLevel == 2) {
        Instance* instance = NULL;
        foreach(Module* m, modules)
        {
	    instance = m->getInstance(selectedText.toLocal8Bit().data());
            if (instance != NULL)
		break;
        }
        PropertyDialog* dialog = new PropertyDialog(0, instance);
	QObject::connect(dialog, SIGNAL(finished(int)), this, SLOT(updateView()));
        dialog->show();
    } else if (hierarchyLevel == 1) {
        Module* module;
        foreach(Module* m, modules)
        {
            if (m->name().c_str() == selectedText)
            {
                module = m;
            }
        }
        ModulePropertyDialog* moduleDialog = new ModulePropertyDialog(0, module);
	QObject::connect(moduleDialog, SIGNAL(finished(int)), this, SLOT(updateView()));
        moduleDialog->show();
    }
//    QString showString = QString("%1, Level %2").arg(selectedText).arg(hierarchyLevel);
//    setWindowTitle(showString);
}

void
MainWindow::executeTclCommand()
{
	QString str = ui->commandline->toPlainText();
    Tcl_Eval(tcl_interp_, str.toLocal8Bit().data());
    ui->logView->setPlainText(ui->commandline->toPlainText());
}


void 
MainWindow::updateView()
{
    initializeTreeView();	
}


void
MainWindow::initializeTreeView()
{
    QTreeView* tree = ui->treeView;
    standardModel = new QStandardItemModel;
	Project* proj = Project::get();	
	Project::ModuleCollection modules = proj->getModules();

    QStandardItem* item = standardModel->invisibleRootItem();
    foreach(Module* m, modules)
    {
        QStandardItem* preparedRow = new QStandardItem(m->name().c_str());
        item->appendRow(preparedRow);
        foreach (Instance* inst, m->instances())
        {
            QStandardItem* secondRow = new QStandardItem(inst->name().c_str());
            preparedRow->appendRow(secondRow);
        }
    }
     tree->setModel(standardModel);
     tree->expandAll();

     //selection changes shall trigger a slot
      QItemSelectionModel *selectionModel= tree->selectionModel();
      connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
                  this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
