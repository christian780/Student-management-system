#include "formreg.h"
#include "ui_formreg.h"
//#include "admin.h"

#include <QDialog>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QImage>
#include <QFileDialog>
#include <QBuffer>


formreg::formreg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::formreg)
    , tcpSocket(new QTcpSocket(this))

{
    ui->setupUi(this);
    QDialog dialog;

    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *widget = new QWidget();
    scrollArea->setWidget(widget);

     setWindowTitle("REGISTER");

    connect(ui->imagebutn, &QPushButton::clicked, this, formreg::on_imagebutn_clicked);
     connect(ui->Register_buttn, &QPushButton::clicked, this, formreg::on_Register_buttn_clicked);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &formreg::handleServerResponse);
//     connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &formreg::displayError);
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);




}

formreg::~formreg()
{
    delete ui;
}

/*
void formreg::handleResponse() {
    QByteArray response = tcpSocket->readAll();
    qDebug() << "Server response:" << response;
    emit responseReceived(response);
    tcpSocket->disconnectFromHost();
}

*/
void formreg::handleServerResponse()
{
    QByteArray response = tcpSocket->readAll();
    qDebug() << "Server response:" << response;

    if (response == "Student registered.") {
        QMessageBox::information(this, "Regsitered", "Registration successful");

    }
    else if( response == "Not Registered."){
        QMessageBox::warning(this, "Error", "Not Registered.");

    }else {
        QMessageBox::critical(this, "Error", "Not registered: " + QString(response));
    }

    // Disconnect after handling response
    //    tcpSocket->disconnectFromHost();
    if(tcpSocket->isOpen()){

        tcpSocket->close();
        qDebug()<< "connection closed";
    }

}



void formreg::on_imagebutn_clicked()
{




    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (filePath.isEmpty()) {
        return;
    }

    QImage image(filePath);

    // Validate image format and size
    if (image.isNull()) {
        QMessageBox::warning(this, "Invalid Image", "The selected file is not a valid image.");
        return;
    }

    if (!image.format() == QImage::Format_ARGB32 && !image.format() == QImage::Format_RGB32) {
        QMessageBox::warning(this, "Invalid Format", "The image is not in PNG format.");
//        reply->deleteLater();
        return;
    }

    if (image.sizeInBytes() > 100 * 1024) {
        QMessageBox::warning(this, "Image Too Large", "The image size must be less than 100 KB.");
        return;
    }

    // Resize to 300x300 while maintaining aspect ratio
    QImage resizedImage = image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

     ui->label_2->setPixmap(QPixmap::fromImage(resizedImage));



//     QImage image("path/to/image.png");
     QByteArray imageData;
     QBuffer buffer(&imageData);
     buffer.open(QIODevice::WriteOnly);
     image.save(&buffer, "PNG");
     QByteArray imageBase64 = imageData.toBase64();



    // Store imageData (e.g., send to server or save in database)
    studentImage = imageBase64; // Assuming studentImage is a QByteArray member variable

    QMessageBox::information(this, "Success", "Image uploaded successfully!");



}


void formreg::on_Register_buttn_clicked()
{
    QString firstname = ui->first_name->text();
    QString lastname = ui->lastname->text();
    QString middlename = ui->middlname->text();
    QString  mobile = ui->mobilenum->text();
    QString address = ui->contact->text();
    QString classvalue = ui->class_2->text();
    QString email = ui->email->text();
    QByteArray image = studentImage;
//    QString gender = ui->maleradio->isChecked();



    QString gender;
    if (ui->maleradio->isChecked()) {
        gender = "Male";
    } else if (ui->female_radio->isChecked()) {
        gender = "Female";
    } else if (ui->other->isChecked()) {
        gender = "Other";
    }




QByteArray requestData = "REGISTER:" + firstname.toUtf8() + ":" + lastname.toUtf8() + ":" + address.toUtf8() + ":" + email.toUtf8() + ":" + mobile.toUtf8() + ":"
                                                  + middlename.toUtf8() + ":"
                                                     + gender.toUtf8() + ":" +classvalue.toUtf8() + ":"+ image;


     qDebug() << "Request Data: " << requestData;

 //   socket->connectToHost("127.0.0.1", 1234);

     tcpSocket->connectToHost(QHostAddress::LocalHost, 1234);
     if(tcpSocket->waitForConnected(3000)){
         if(tcpSocket->isWritable()){
             tcpSocket->write(requestData);
             qDebug()<<"request sent" << requestData;
             tcpSocket->waitForBytesWritten(1000);

         }

         qDebug()<< "connected to server ";
     }
     else{
         qDebug()<<"unable to connect to server";
     }





     ///Handle errors


}


/*
void formreg::displayError(QAbstractSocket::SocketError socketError)
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


/*
void Admin::on_uploadButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (filePath.isEmpty()) {
        return;
    }

    QImage image(filePath);

    // Validate image format and size
    if (image.isNull()) {
        QMessageBox::warning(this, "Invalid Image", "The selected file is not a valid image.");
        return;
    }

    // Resize to 300x300 while maintaining aspect ratio
    QImage resizedImage = image.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Compress image to PNG format
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    resizedImage.save(&buffer, "PNG");

    // Check size limit (100 KB)
    if (imageData.size() > 100 * 1024) {
        QMessageBox::warning(this, "Image Too Large", "The image size must be less than 100 KB.");
        return;
    }

    // Store imageData (e.g., send to server or save in database)
    studentImage = imageData; // Assuming studentImage is a QByteArray member variable

    QMessageBox::information(this, "Success", "Image uploaded successfully!");
}

*/
