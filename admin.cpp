#include "admin.h"
#include "ui_admin.h"
#include "hashpass.h"
#include "adminpanel.h"

#include "regform.h"

#include <QString>
#include <QNetworkInterface>
#include <QtNetwork>
#include <QtWidgets>
#include <QJsonObject>
#include <QLocalServer>
//#include <bcrypt.h>

Admin::Admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin)
    , tcpSocket(new QTcpSocket(this))

{
    ui->setupUi(this);
   ui->username->setPlaceholderText("Enter your username");
    ui->password->setPlaceholderText("Enter your password");
    ui->password->setEchoMode(QLineEdit::Password);

    setWindowTitle("LOGIN");





     connect(ui->login, &QPushButton::clicked, this, &Admin::on_login_clicked);
    connect(tcpSocket,  &QTcpSocket::readyRead, this, &Admin::handleServerResponse);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &Admin::displayError);
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);



}

Admin::~Admin()
{
    delete ui;
   // db.close();

}




/*
void Admin::handleResponse() {
    QByteArray response = tcpSocket->readAll();
    qDebug() << "Server response:" << response;
    emit responseReceived(response);
    tcpSocket->disconnectFromHost();
}
*/


void Admin::handleServerResponse()
{
    QByteArray response = tcpSocket->readAll();
    qDebug() << "Server response:" << response;

    if (response == "Authentication successful") {
        QMessageBox::information(this, "Login Success", "Welcome Admin");
        // Transition to the next screen, such as the admin dashboard
        Adminpanel *adp = new Adminpanel();
        adp->show();
        this->close();

    } else if( response == "Authentication failed"){
          QMessageBox::warning(this, "Login Failed", "Invalid username or password.");

    }else {
        QMessageBox::critical(this, "Error", "Unknown server response: " + QString(response));
    }

    // Disconnect after handling response
     tcpSocket->disconnectFromHost();
/*
    if(tcpSocket->isOpen()){

        tcpSocket->close();
        qDebug()<< "connection closed";
    }
*/
}




void Admin::on_login_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();




    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;

    }


    // Prepare request
   QByteArray request = "AUTHENTICATE:" + username.toUtf8() + ":" + password.toUtf8();



    // Connect to the server and send the request
    tcpSocket->connectToHost("127.0.0.1", 1234);
   if(tcpSocket->waitForConnected(3000)){
        if(tcpSocket->isWritable()){
           tcpSocket->write(request);
            qDebug()<<"request sent" << request;
            tcpSocket->waitForBytesWritten(1000);

        }

        qDebug()<< "connected to server ";
   }
   else{
           qDebug()<<"unable to connect to server";
   }

}


void Admin::displayError(QAbstractSocket::SocketError socketError)
{
    QString errorMessage;

    switch (socketError) {
    case QAbstractSocket::OperationError:
        // Log the error but do not show a message box
        qWarning() << "Non-critical socket error:" << tcpSocket->errorString();
        return; // Exit the function early
    case QAbstractSocket::ConnectionRefusedError:
        errorMessage = "The connection was refused by the server. Please ensure the server is running.";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        errorMessage = "The server closed the connection unexpectedly.";
        break;
    case QAbstractSocket::HostNotFoundError:
        errorMessage = "The server address was not found. Please check the server address.";
        break;
    case QAbstractSocket::SocketTimeoutError:
        errorMessage = "The connection timed out. Please check your network.";
        break;
    default:
        errorMessage = "An unknown error occurred: " + tcpSocket->errorString();
        break;
    }

    // Show the message box only for critical errors
    QMessageBox::information(this, tr("Socket Error"), errorMessage);
}


/*
void Admin::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                     .arg(tcpSocket->errorString()));
    }

//    getFortuneButton->setEnabled(true);
}

*/


