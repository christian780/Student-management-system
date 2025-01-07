#include "sessionmanager.h"

SessionManager::SessionManager() {

    // Define static members
    currentUsername = "admin";
    userType = "admin";


    SessionManager::currentUsername = "admin";
    SessionManager::userType = "admin";


}

void SessionManager::clearSession()
{
    currentUsername.clear();
    userType.clear();
}
