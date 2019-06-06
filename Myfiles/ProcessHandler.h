#ifndef PROCESS_HANDLER
#define PROCESS_HANDLER
#include "my_server.hpp"
#include "sha256.h"
#include "User.h"
#include "Publisher.h"
#include "ExceptionHandler.h"
#include "UsersRepository.h"
#include "MovieRepository.h"
#include "AI.h"
#include <string>
#include <map>
#include <iterator>
#define HAS_ERROR 1
#define NO_ERROR 0
typedef unsigned int Counter;
typedef std::map<std::string,std::string> Map;
typedef std::map<std::string,User*> Active;
class ProcessHandler
{
    public:
        ProcessHandler(UsersRepository* users,MovieRepository* movies);
        std::string signup(Map signupInput,std::string function_type);
        std::string login(Map loginInput,std::string function_type);
        void logout(std::string session_id);
        void checkFunctions(std::string function_type,Map input);
    private:
        Active active_users;
        MovieRepository* movie_repository;
        UsersRepository* users_repository;
        void checkPermission(std::string function_type);
        void checkValues(Map input);
        void checkEmailSyntax(std::string email);
        bool isNumber(std::string str);
        bool isFloat(std::string str);
        void followHandler(Map input);
        void notificationHandler(Map input,std::string function);
        void submitNotifHandler(Map input);
        void followNotifHandler(Map input);
        void replyNotifHandler(Map input);
        void commentNotifHandler(Map input);
        void buyNotifHandler(Map input);
        void rateNotifHandler(Map input);
        void buyHandler(Map input);
        AI recommendationHandler();
};
#endif