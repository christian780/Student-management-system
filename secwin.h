#ifndef SECWIN_H
#define SECWIN_H

#include "admin.h"
#include "dialog.h"

#include <QMainWindow>
#include <iostream>


class Admin;

namespace Ui {
class secwin;
}



class secwin : public QMainWindow
{
    Q_OBJECT

public:
    explicit secwin(QWidget *parent = nullptr);
    ~secwin();

private slots:
    void on_pushButton_clicked();

//    void on_label_3_linkActivated(const QString &link);


    void on_dashboardui_clicked();

    void on_stafflogin_clicked();

    void on_actionExit_triggered();

    void on_actionStaff_Form_triggered();

private:
    Ui::secwin *ui;
    Admin *ad;
     bool loggedOut;


};

#endif // SECWIN_H
