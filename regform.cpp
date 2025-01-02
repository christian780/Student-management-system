#include "regform.h"
#include "ui_regform.h"
#include "admin.h"
#include "hashpass.h"





#include <QRegularExpressionValidator>



regform::regform(Admin *ad, QWidget *parent)
    : QDialog(parent)
    ,ui(new Ui::regform)
    ,admin(ad)
{
    ui->setupUi(this);

    ui->passwrd->setEchoMode(QLineEdit::Password);
    ui->confirmpass->setEchoMode(QLineEdit::Password);



    setWindowTitle("User Registration");


    // Connect the signup button's clicked signal to the on_signup_clicked slot
 //   connect(ui->signup, &QPushButton::clicked, this, &regform::on_signup_clicked);
//    connect(ui->login, &QPushButton::clicked, this, &Admin::on_login_clicked);


}

regform::~regform()
{
    delete ui;
}

/*
void regform::on_signup_clicked()
{
//      QSqlDatabase db = admin->getDatabase();

 //   QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qCritical() << "Database is not open during registration.";
        QMessageBox::critical(this, "Error", "Database is not open.");
        return;
    }


    QString name = ui->Name->text();
    QString passid = ui->passwrd->text();
    QString idconf = ui->confirmpass->text();
    QString email = ui->email->text();
    QString mobileStr = ui->mobileno->text();
    qint64 mobileNumber = mobileStr.toLongLong(); // Convert text to a 64-bit integer

    // Ensure password confirmation matches
    if (passid != idconf) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
//        qCritical() << "Password and confirmation do not match!";
        return;
    }

     QString salt = generateSalt();
    qDebug() << "Generated Salt:" << salt;
    QString hashedPassword = hash_Password(passid, salt);
    qDebug() << " Hashed Password:" << hashedPassword;


    db.transaction();

    QSqlQuery query(db);
    query.prepare("INSERT INTO admin (user, password, salt,  mobile, email) "
                  "VALUES (:user, :password, :salt, :mobile, :email)");
    query.bindValue(":user", name);
    query.bindValue(":password", hashedPassword); // Store hashed password
    query.bindValue(":salt", salt);
    query.bindValue(":email", email);
    query.bindValue(":mobile", mobileNumber);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "User registered successfully.");
        //qDebug() << "User registered successfully!";
        this->close();
    } else {
        db.rollback();
        qCritical() << "Failed to register user:" << query.lastError().text();
    }
}

*/


