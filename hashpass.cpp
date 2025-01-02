#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QVariant>


#include "hashpass.h"



QString generateSalt(int length) {
    const QString possibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    QString salt;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
        salt.append(possibleCharacters.at(index));
    }
    return salt;
}




QString hash_Password(const QString &password, const QString &salt) {
    QString saltedPassword = password + salt;
    QByteArray hashed = QCryptographicHash::hash(saltedPassword.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}
