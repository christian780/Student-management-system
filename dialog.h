#ifndef DIALOG_H
#define DIALOG_H

//#include "mainwindow.h"


#include <QTimer>
#include <QDialog>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void updateProgress();

    void on_Dialog_accepted();

private:
    Ui::Dialog *ui;
//    QWindow* win;

};

#endif // DIALOG_H
