#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//    ,di(new Dialog())
//    ,timer(new QTimer(this))
//    ,w(new QMainWindow())
{
    ui->setupUi(this);
 //   Dialog *di;


//    connect(timer, &QTimer::timeout, this, &MainWindow::showdialog);



  //   di->show();
 //   showdialog();


}

MainWindow::~MainWindow()
{
    delete ui;
//    delete timer;
 //   delete di;


}

/*void MainWindow::showdialog(){

   timer->stop();
    di->exec();
    w->show();
}
*/
