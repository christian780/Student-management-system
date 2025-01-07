#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>


class SessionManager
{
public:
    SessionManager();


    QString currentUsername;
      QString userType;

      void clearSession();
};



#endif // SESSIONMANAGER_H
