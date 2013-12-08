#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>

class QStandardItemModel;
class Module;
class Net;
class Tcl_Interp;

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

private:
    void initializeTreeView();
    QList<Module> getTestModules();
    Net getNet();
    
private:
    Ui::MainWindow *ui;
    QStandardItemModel* standardModel;
    Tcl_Interp* tcl_interp_;
};

#endif // MAINWINDOW_H
