#ifndef PROCESS_HANDLER
#define PROCESS_HANDLER
#include "User.h"
#include <map>
class ProcessHandler
{
    public:
        ProcessHandler();
        void signup();
        void login();
        void checkFunctions();
    private:
        User* active_user;
};
#endif