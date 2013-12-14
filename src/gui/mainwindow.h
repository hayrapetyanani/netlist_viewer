#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>

class QStandardItemModel;
class Module;
class Net;
class Tcl_Interp;
class QTreeView;
class QTextEdit;
class QListView;
class QPushButton;
class QTextEdit;
class QMenuBar;
class QMenu;
class QToolBar;
class QStatusBar;
class drawing_widget;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void executeTclCommand();
    void selectionChangedSlot(const QItemSelection &, const QItemSelection &);
    void updateView();
    void addModuleSlot();
    
private:
    void initializeTreeView();
    QList<Module> getTestModules();
    Net getNet();
    void registerCommands();
    void addMenuBar();
    void setup();

private:
    QStandardItemModel* standardModel;
    Tcl_Interp* tcl_interp_;
    QMenu* fileMenu;

    QAction *actionOPen;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QTreeView *treeView;
    QTextEdit *commandline;
    drawing_widget* canvas;
    QPushButton *executeButton;
    QTextEdit *logView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;


};

#endif // MAINWINDOW_H
