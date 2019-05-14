#ifndef PROCESS_HANDLER
#define PROCESS_HANDLER
#include "User.h"
#include <map>
typedef std::map<std::string,std::string> Map;
class ProcessHandler
{
    public:
        ProcessHandler();
        void signup(Map signupInput);
        void login(Map loginInput);
        void checkFunctions(std::string,Map input);
    private:
        User* active_user;
};
#endif