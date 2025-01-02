#include "secwin.h"
#include "ui_secwin.h"
//#include "adminpanel.h"
#include "schlserver.h"

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
