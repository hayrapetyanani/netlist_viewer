#ifndef MODULEPROPERTYWINDOW_H
#define MODULEPROPERTYWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <../database/module.hpp>
#include <../database/project.hpp>

class ModulePropertyDialog : public QDialog
{
  Q_OBJECT
public:
    ModulePropertyDialog(QWidget* parent = 0, Module* modl = 0);
public slots:
    void saveData();
private:
    QLabel* nameLabel;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QLineEdit *nameEdit;
    QLineEdit* portNameEdit;
    Module* module;
};

#endif // MODULEPROPERTYWINDOW_H
