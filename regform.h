#ifndef REGFORM_H
#define REGFORM_H


#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

class Admin;

namespace Ui {
class regform;
}



class regform : public QDialog
{
    Q_OBJECT

public:
    explicit regform(Admin *ad, QWidget *parent = nullptr);
//    explicit regform(QWidget *parent = nullptr);
    ~regform();




 // Custom signal emitted after successful registration

/*
private slots:
    void on_signup_clicked();
*/


private:
    Ui::regform *ui;
    QSqlDatabase dbase;
    Admin *admin;



};

#endif // REGFORM_H
