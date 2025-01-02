#include "adminpanel.h"
#include "ui_adminpanel.h"
#include  "formreg.h"
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



