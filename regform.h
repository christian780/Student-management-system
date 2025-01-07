#ifndef REGFORM_H
#define REGFORM_H

#include <QTcpSocket>
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
//    explicit regform(Admin *ad, QWidget *parent = nullptr);
    explicit regform(QWidget *parent = nullptr);
    ~regform();


public slots:
     void handleServerResponse();

 // Custom signal emitted after successful registration


private slots:
    void on_signup_clicked();
    void displayError(QAbstractSocket::SocketError socketError);




private:
    Ui::regform *ui;
    QSqlDatabase dbase;
 //   Admin *admin;
    QTcpSocket *tcpSocket = nullptr;



};

#endif // REGFORM_H
