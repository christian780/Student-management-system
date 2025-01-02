#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
//#include <QSqlDatabase>
//#include <QSqlQuery>
#include <QMessageBox>
//#include <QSqlError>
//#include <QSql>

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include <QtWidgets>


//#include "adminpanel.h"

//class Adminpanel;
class QTcpSocket;
//class QComboBox;


#include <QDialog>


namespace Ui {
class Admin;
}

const auto USER_TABLE = QLatin1String(R"(
    SELECT user, password, salt from admin WHERE user= :user AND password = :password
    )");

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

//    QSqlDatabase getDatabase() const;
//    void sendRequest(const QString &host, quint16 port, const QString username, const QString &password);
    //


public slots:

    void on_login_clicked();
     void handleServerResponse();
signals:
    void responseReceived(const QByteArray &response);


private slots:
//    void on_pushButton_clicked();

//    void handleResponse();




private:
    Ui::Admin *ui;
//    Adminpanel *adp;
//    QSqlDatabase db;
    bool connectToDatabase();
  QTcpSocket *tcpSocket = nullptr;
    QComboBox *hostCombo = nullptr;
    void displayError(QAbstractSocket::SocketError socketError);



//    void showError(const QSqlError &err);

};

#endif // ADMIN_H
