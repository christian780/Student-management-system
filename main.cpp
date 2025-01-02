#include "mainwindow.h"
#include "secwin.h"
#include "admin.h"
//#include "adminpanel.h"
#include "regform.h"
#include "schlserver.h"
#include "formreg.h"

#include <QApplication>


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Admin;
class formreg;
/*
bool setupDatabase() {
    // Add a database connection with a connection name
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "shared_connection");
    db.setDatabaseName("C:/proj/smp/admin2.db");

    if (!db.open()) {
        qCritical() << "Database connection failed:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully.";
    return true;
}
*/
/*
bool writeToDatabase(const QString &username, const QString &password, const QString &email, qint64 mobile) {
    Admin admin;

   QSqlDatabase db = admin.getDatabase();  // Assumes a connection has been established

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query =  QSqlQuery(db);
    query.prepare("INSERT INTO admin (user, password, salt, mobile, email) VALUES (:user, :password, :salt, :mobile, :email)");
    query.bindValue(":user", username);
    query.bindValue(":password", password); // Hash the password before binding it
    query.bindValue(":salt", "random_salt"); // Generate a salt for hashing
    query.bindValue(":mobile", mobile);
    query.bindValue(":email", email);

    if (query.exec()) {
        qDebug() << "Data inserted successfully!";
        return true;
    } else {
        qCritical() << "Error inserting data:" << query.lastError().text();
        return false;
    }
}

*/
/*
bool verifyDataInserted(const QString &username) {

     QSqlDatabase db = admin->getDatabase();
    QSqlQuery query =  QSqlQuery(db);
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec()) {
        if (query.next()) {
            qDebug() << "Data found for user:" << query.value("username").toString();
            return true;
        } else {
            qDebug() << "No data found for user:" << username;
            return false;
        }
    } else {
        qCritical() << "Error reading data:" << query.lastError().text();
        return false;
    }
}
*/
/*bool deleteAllUsers() {

    Admin admin;


     QSqlDatabase db = admin.getDatabase();
    QSqlQuery query =  QSqlQuery(db);
    if (query.exec("DELETE FROM admin")) {
        qDebug() << "All users deleted successfully.";
        return true;
    } else {
        qCritical() << "Error deleting all users:" << query.lastError().text();
        return false;
    }
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 // Admin loginScreen;


//    MainWindow w;
   secwin secw;
    Dialog d;
    d.exec();
//    loginScreen.exec();



     secw.show();
    Admin adm;
     formreg reg;

    return a.exec();
}


/*bool status;

status = deleteAllUsers();
if(status == true){
    qDebug() << "success";
}
*/

/*
const QString username = "admin";
const QString password = "admin";
const QString email = NULL;
qint64  mobile = 0;

bool status =   writeToDatabase( username,  password,  email,  mobile);
if(status == true){
    qDebug()<<"success";

}
*/
