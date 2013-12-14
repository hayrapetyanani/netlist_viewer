#include "mainwindow.h"
#include "drawing_widget.hpp"
#include "../database/module.hpp"
#include "../database/project.hpp"

#include <tcl.h>
#include <propertywindow.h>
#include <modulepropertywindow.h>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <assert.h>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tcl_interp_ = Tcl_CreateInterp();
    setup();
    initializeTreeView();
    registerCommands();
    addMenuBar();
}

void 
MainWindow::setup()
{
    Project* p = Project::get();                                           
    p->loadGraph();
    QMainWindow *mainWindow = this;
    mainWindow->setObjectName(QString::fromUtf8("Netlist Viewer"));
    mainWindow->resize(694, 426);
    actionOPen = new QAction(mainWindow);
    actionOPen->setObjectName(QString::fromUtf8("actionOPen"));
    actionExit = new QAction(mainWindow);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionAbout = new QAction(mainWindow);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    centralWidget = new QWidget(mainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    treeView = new QTreeView(centralWidget);
    treeView->setObjectName(QString::fromUtf8("treeView"));
//    treeView->setGeometry(QRect(0, 0, 221, 251));
    canvas = new drawing_widget(centralWidget);
    //propertyView->setObjectName(QString::fromUtf8("propertyView"));
//    propertyView->setGeometry(QRect(220, 0, 471, 251));

    QHBoxLayout* upperLayout = new QHBoxLayout();
    upperLayout->addWidget(treeView);
    upperLayout->addWidget(canvas);

    commandline = new QTextEdit(centralWidget);
    commandline->setObjectName(QString::fromUtf8("commandline"));
//    commandline->setGeometry(QRect(0, 340, 611, 31));
    executeButton = new QPushButton(centralWidget);
    executeButton->setObjectName(QString::fromUtf8("executeButton"));
//    executeButton->setGeometry(QRect(610, 340, 81, 27));
    
    QHBoxLayout* lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(commandline);
    lowerLayout->addWidget(executeButton);

    logView = new QTextEdit(centralWidget);
    logView->setObjectName(QString::fromUtf8("logView"));
    QHBoxLayout* middleLayout = new QHBoxLayout();
    middleLayout->addWidget(logView);


//    logView->setGeometry(QRect(0, 250, 691, 91));
 
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(lowerLayout);
    centralWidget->setLayout(mainLayout);

   
    mainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(mainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
//    menuBar->setGeometry(QRect(0, 0, 694, 25));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    mainWindow->setMenuBar(menuBar);
    mainToolBar = new QToolBar(mainWindow);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    mainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(mainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    mainWindow->setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addSeparator();
    menuFile->addAction(actionOPen);
    menuFile->addAction(actionExit);
    menuHelp->addAction(actionAbout);

    QMetaObject::connectSlotsByName(mainWindow);
} // setupUi


    void 
MainWindow::addMenuBar()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    QMenu* newMenu = fileMenu->addMenu("&New");
    newMenu->addAction("&Project");
    QAction* moduleAct = newMenu->addAction("&Module");
    newMenu->addAction("&Instance");
    newMenu->addAction("&Net");
    
    moduleAct->setStatusTip(tr("Add new module to the project"));
    connect(moduleAct, SIGNAL(triggered()), this, SLOT(addModuleSlot()));
}

void 
MainWindow::addModuleSlot()
{
    Tcl_Eval(tcl_interp_, "module:add moduleSlot1"); 
    ModulePropertyDialog* moduleDialog = new ModulePropertyDialog(0, NULL);
    QObject::connect(moduleDialog, SIGNAL(finished(int)), this, SLOT(updateView()));
    moduleDialog->show();
}

void MainWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
    //get the text of the selected item
    const QModelIndex index = treeView->selectionModel()->currentIndex();
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
        Module* module = NULL;
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
	QString str = commandline->toPlainText();
    Tcl_Eval(tcl_interp_, str.toLocal8Bit().data());
    logView->append(commandline->toPlainText());
    commandline->clear();
    updateView();
}

int addModule(ClientData, Tcl_Interp *, int ,
        Tcl_Obj *const objv[])
{
    std::string arg1 = objv[1]->bytes;

    Project* p = Project::get();

    assert(0 != p);
    p->addModule(arg1);

    return TCL_OK;
}

int addInstance(ClientData, Tcl_Interp *, int ,
        Tcl_Obj *const objv[])
{
    std::string arg1 = objv[1]->bytes;
    std::string arg2 = objv[2]->bytes;
    std::string arg3 = objv[3]->bytes;

    Project* p = Project::get();

    assert(0 != p);
    Module* parent_module = p->getModule(arg1);
    if (parent_module == NULL) return TCL_ERROR;
    Module* master_module = p->getModule(arg2);
    if (master_module == NULL) return TCL_ERROR;
    parent_module->addInstance(arg3, master_module);
    return TCL_OK;
}
Instance* getInstance(Project* p, const std::string instName)
{
    Project::ModuleCollection modules = p->getModules();
    Instance* instance = NULL;
    foreach(Module* m, modules)
    {
        instance = m->getInstance(instName);
        if (instance != NULL)
            break;
    }
    return instance;
}

int addNet(ClientData, Tcl_Interp *, int ,
        Tcl_Obj *const objv[])
{
    std::string arg1 = objv[1]->bytes;
    std::string arg2 = objv[2]->bytes;
    std::string arg3 = objv[3]->bytes;

    Project* p = Project::get();

    assert(0 != p);
    
    Project::ModuleCollection modules = p->getModules();
    Instance* instance1 = getInstance(p, arg1); 
    if (instance1 == NULL) return TCL_ERROR;
    Instance* instance2 = getInstance(p, arg2); 
    if (instance2 == NULL) return TCL_ERROR;
//    p->addNet(arg3, instance1, instance2);
    return TCL_OK;
}

int removeModule(ClientData, Tcl_Interp *, int ,
        Tcl_Obj *const objv[])
{
    std::string arg1 = objv[1]->bytes;

    Project* p = Project::get();

    assert(0 != p);
    bool done = p->removeModule(arg1);

    return done ? TCL_OK : TCL_ERROR;
}
void 
MainWindow::registerCommands()
{
    assert(tcl_interp_);
    Tcl_CreateObjCommand(tcl_interp_, "module:add", addModule, 0, 0);
    Tcl_CreateObjCommand(tcl_interp_, "module:remove", removeModule, 0, 0);
    Tcl_CreateObjCommand(tcl_interp_, "instance:add", addInstance, 0, 0);
   // Tcl_CreateObjCommand(tcl_interp_, "instance:remove", removeInstance, 0, 0);
    Tcl_CreateObjCommand(tcl_interp_, "net:add", addNet, 0, 0);
    
    
    
    QObject::connect(executeButton, SIGNAL(clicked()), this, SLOT(executeTclCommand()));
}


void 
MainWindow::updateView()
{
    initializeTreeView();	
}


void
MainWindow::initializeTreeView()
{
    QTreeView* tree = treeView;
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
//    delete standardModel;
//    delete centralWidget;
//    delete treeView;
//    delete commandline;
//    delete propertyView;
//    delete executeButton;
//    delete logView;
//    delete menuBar;
//    delete menuFile;
//    delete menuHelp;
//    delete mainToolBar;
//    delete statusBar;
}
