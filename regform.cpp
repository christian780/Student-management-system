#include "regform.h"
#include "ui_regform.h"
#include "admin.h"
#include "hashpass.h"
#include "secwin.h"





#include <QRegularExpressionValidator>



regform::regform( QWidget *parent)
    : QDialog(parent)
    ,ui(new Ui::regform)
    , tcpSocket(new QTcpSocket(this))

{
    ui->setupUi(this);

    ui->passwrd->setEchoMode(QLineEdit::Password);
    ui->confirmpass->setEchoMode(QLineEdit::Password);



    setWindowTitle("Account Registration");


    // Connect the signup button's clicked signal to the on_signup_clicked slot
      connect(ui->signup, &QPushButton::clicked, this, &regform::on_signup_clicked);
    connect(tcpSocket,  &QTcpSocket::readyRead, this, &regform::handleServerResponse);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &regform::displayError);
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);
//    connect(ui->login, &QPushButton::clicked, this, &Admin::on_login_clicked);


}

regform::~regform()
{
    delete ui;
}

void regform::handleServerResponse()
{
    QByteArray response = tcpSocket->readAll();
    qDebug() << "Server response from regform:" << response;

    if (response == "registered.") {
        QMessageBox::information(this, "Account", "Account Added");
        // Transition to the next screen, such as the admin

    } else if( response == "Account_Not_Added"){
        QMessageBox::warning(this, " Accont Fail", "Account not Added.");

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


void regform::displayError(QAbstractSocket::SocketError socketError)
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


void regform::on_signup_clicked()
{
//      QSqlDatabase db = admin->getDatabase();

 //   QSqlDatabase db = QSqlDatabase::database();



    QString name = ui->Name->text();
    QString password = ui->passwrd->text();
    QString confirmpass = ui->confirmpass->text();
    QString email = ui->email->text();
    QString mobileStr = ui->mobileno->text();
    qint64 mobileNumber = mobileStr.toLongLong(); // Convert text to a 64-bit integer

    // Ensure password confirmation matches
    if (password != confirmpass) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
//        qCritical() << "Password and confirmation do not match!";
        return;
    }

    if (name.isEmpty() || password.isEmpty() || mobileStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;

    }


    // Prepare request
//    QByteArray reques = "AUTHENTICATE:" + username.toUtf8() + ":" + password.toUtf8();

    // Prepare request
    QByteArray request = "ACCOUNTREG:" + name.toUtf8() + ":" + password.toUtf8() + ":" + email.toUtf8()  + ":" + mobileStr.toUtf8();


     QString salt = generateSalt();
    qDebug() << "Generated Salt:" << salt;
    QString hashedPassword = hash_Password(password, salt);
    qDebug() << " Hashed Password:" << hashedPassword;

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




