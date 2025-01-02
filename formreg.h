#ifndef FORMREG_H
#define FORMREG_H

#include <QDialog>
#include <QTcpSocket>

//#include "admin.h"

class QTcpSocket;
class Admin;

namespace Ui {
class formreg;
}


class formreg : public QDialog
{
    Q_OBJECT

public:
    explicit formreg(QWidget *parent = nullptr);
    ~formreg();
//     QTcpSocket *socket;

signals:
     void responseReceived(const QByteArray &response);

private slots:

    void on_imagebutn_clicked();
//    void displayError(QAbstractSocket::SocketError socketError);




    void on_Register_buttn_clicked();
//    void handleResponse();
    void handleServerResponse();

private:
    Ui::formreg *ui;
    Admin *ad;
    QTcpSocket *tcpSocket = nullptr;

};

#endif // FORMREG_H
