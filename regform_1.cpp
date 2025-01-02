#include "regform_1.h"
#include "ui_regform_1.h"

regForm_1::regForm_1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::regForm_1)
{
    ui->setupUi(this);
}

regForm_1::~regForm_1()
{
    delete ui;
}

void regForm_1::on_comboBox_activated(int index)
{

}

