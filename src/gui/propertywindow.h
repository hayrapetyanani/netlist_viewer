#ifndef PROPERTYWINDOW_H
#define PROPERTYWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <../database/instance.hpp>
#include <../database/module.hpp>

class PropertyDialog : public QDialog
{
  Q_OBJECT
public:
    PropertyDialog(QWidget* parent = 0, Instance* inst = 0);
public slots:
    void saveData();
private:
    QLabel* nameLabel;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QLineEdit *nameEdit;
    QLabel *masterNameEdit;
    QLineEdit *parentNameEdit;
    QLabel* masterNameLabel;
    QLabel* parentNameLabel;
    Instance* instance;
    std::string instanceName;

};

#endif // PROPERTYWINDOW_H
