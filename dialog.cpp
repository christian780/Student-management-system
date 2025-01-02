#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

#include <QProgressBar>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)


{

    ui->setupUi(this);
    Dialog::setFixedHeight(360);
    Dialog::setFixedWidth(726);



    // Set the range of the progress bar (0 to 100)
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);  // Set initial progress to 0%
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);


    // Create a QTimer that will update the progress bar automatically
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::updateProgress);
    timer->start(100);    // Set the timer interval




}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::updateProgress()
{

    // Get the current progress value
    int currentValue = ui->progressBar->value();

    // If the progress is less than 100%, increment it
    if (currentValue < 100) {
        ui->progressBar->setValue(currentValue + 1);


    }else{
        this->hide();
    }
}


void Dialog::on_Dialog_accepted()
{

}

