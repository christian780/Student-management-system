#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"


#include <QTimer>
#include <QMainWindow>




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void showdialog();


private:
   Ui::MainWindow *ui;
//   QTimer *timer;
//   QMainWindow *w;
 //    Dialog *di;

};
#endif // MAINWINDOW_H
