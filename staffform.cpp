#include "staffform.h"
#include "ui_staffform.h"

staffform::staffform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::staffform)
{
    ui->setupUi(this);


    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *widget = new QWidget();
    scrollArea->setWidget(widget);

}

staffform::~staffform()
{
    delete ui;
}
