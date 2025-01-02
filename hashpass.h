#ifndef HASHPASS_H
#define HASHPASS_H

#include <windows.h>
#include <QString>
#include <QByteArray>



QString generateSalt(int length = 16);
QString hash_Password(const QString &password, const QString &salt);


#endif // HASHPASS_H
