#include "stafflogin.h"
#include "ui_stafflogin.h"
#include "staffprofile.h"

class StaffProfile;

stafflogin::stafflogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::stafflogin)
    , tcpSocket(new QTcpSocket(this))

{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Enter your username");
    ui->password->setPlaceholderText("Enter your password");
    ui->password->setEchoMode(QLineEdit::Password);


    setWindowTitle("LOGIN");

    connect(ui->login, &QPushButton::clicked, this, &stafflogin::on_login_clicked);
    connect(tcpSocket,  &QTcpSocket::readyRead, this, &stafflogin::handleServerResponse);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &stafflogin::displayError);
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);


}

stafflogin::~stafflogin()
{
    delete ui;
}


void stafflogin::handleServerResponse()
{
    QByteArray response = tcpSocket->readAll();
    qDebug() << "Server response to stafflogin:" << response;

    if (response == "STAFFADDED") {
        //       QString userType = QString(response).split(":")[1];

        this->hide();

        QMessageBox::information(this, "Login Success", "Welcome");
        // Transition to the next screen, such as the admin dashboard
        StaffProfile *staff = new StaffProfile();
        staff->exec();

    }
    else if( response == "ERROR"){
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


void stafflogin::on_login_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();




    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;

    }


    // Prepare request
    QByteArray request = "STAFFLOGIN:" + username.toUtf8() + ":" + password.toUtf8();



    // Connect to the server and send the request
    // socket->connectToHost(QHostAddress::LocalHost,8080);
    tcpSocket->connectToHost(QHostAddress::LocalHost, 1234);
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



void stafflogin::displayError(QAbstractSocket::SocketError socketError)
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

