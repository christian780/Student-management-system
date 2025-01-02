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

private:
    Ui::secwin *ui;
    Admin *ad;


};

#endif // SECWIN_H
