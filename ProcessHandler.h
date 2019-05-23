#ifndef PROCESS_HANDLER
#define PROCESS_HANDLER
#include "User.h"
#include "Publisher.h"
#include "ExceptionHandler.h"
#include "UsersRepository.h"
#include "MovieRepository.h"
#include "CommentRepository.h"
#include <string>
#include <map>
#include <iterator>
#define HAS_ERROR 1
#define NO_ERROR 0
typedef unsigned int Counter;
typedef std::map<std::string,std::string> Map;
class ProcessHandler
{
    public:
        ProcessHandler(UsersRepository* users,
            MovieRepository* movies,CommentRepository* comments);
        void signup(Map signupInput);
        void login(Map loginInput);
        void checkFunctions(std::string function_type,Map input);
    private:
        User* active_user;
        MovieRepository* movie_repository;
        UsersRepository* users_repository;
        CommentRepository* comment_repository;
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
};
#endif