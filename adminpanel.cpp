#include "adminpanel.h"
#include "ui_adminpanel.h"
#include  "formreg.h"
#include "regform.h"
#include "sessionmanager.h"
#include "admin.h"

class regform;
class Admin;
class SessionManager;

#include <QMessageBox>

Adminpanel::Adminpanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Adminpanel)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Adminpanel::on_pushButton_clicked);



}

Adminpanel::~Adminpanel()
{
    delete ui;
}

void Adminpanel::on_pushButton_clicked()
{
    formreg *reg = new formreg();
    reg->exec();
}




void Adminpanel::on_staffcard_clicked()
{

}


void Adminpanel::on_actionCreate_Account_triggered()
{
    regform *form = new regform();
    form->exec();
}




void Adminpanel::on_actionCreate_triggered()
{

}


void Adminpanel::on_actionTimetable_triggered()
{

}


void Adminpanel::on_actionClose_triggered()
{
    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,"Exit", "Are you sure you want to exit?",
                                        QMessageBox::Yes| QMessageBox::No).exec())
    {
        this->loggedOut = true;
        exit(EXIT_SUCCESS);
    }

}


void Adminpanel::on_actionLogout_triggered()
{
    SessionManager manager;
    // Clear session data
    manager.clearSession();
    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,"Logout", "Are you sure you want to Logout?",
                                        QMessageBox::Yes| QMessageBox::No).exec())
    {
        this->loggedOut = true;
        this->close();
        // Reopen the login screen
        Admin* login = new Admin();
        login->show();
    }

    // Close the current window




}

