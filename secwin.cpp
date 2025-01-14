#include "secwin.h"
#include "ui_secwin.h"
//#include "adminpanel.h"
#include "schlserver.h"
#include "stafflogin.h"

class stafflogin;

secwin::secwin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::secwin)
{
    ui->setupUi(this);
}

secwin::~secwin()
{
    delete ui;
}

void secwin::on_pushButton_clicked()
{
   ad = new Admin();
   ad->exec();

/*    schlserver server;
    server.exec();
*/
}


/*void::on_label_3_linkActivated(const QString &link)
{

}
*/


void secwin::on_dashboardui_clicked()
{

}


void secwin::on_stafflogin_clicked()
{
    stafflogin *staff = new stafflogin();
    staff->exec();
}


void secwin::on_actionExit_triggered()
{

    if(QMessageBox::Yes == QMessageBox(QMessageBox::Question,"Exit", "Are you sure you want to exit?",
                                        QMessageBox::Yes|QMessageBox::No).exec())
    {
        this->loggedOut = true;
        exit(EXIT_SUCCESS);
    }

}


void secwin::on_actionStaff_Form_triggered()
{

}


void secwin::on_pushButton_8_clicked()
{

}

