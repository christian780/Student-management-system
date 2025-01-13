#ifndef STAFFLOGIN_H
#define STAFFLOGIN_H

#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>


class QTcpSocket;

namespace Ui {
class stafflogin;
}



class stafflogin : public QDialog
{
    Q_OBJECT

public:
    explicit stafflogin(QWidget *parent = nullptr);
    ~stafflogin();

signals:
    void responseReceived(const QByteArray &response);




public slots:
    void on_login_clicked();
     void handleServerResponse();
//    void connectToServer();


private:
    Ui::stafflogin *ui;
    QTcpSocket *tcpSocket = nullptr;
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // STAFFLOGIN_H
