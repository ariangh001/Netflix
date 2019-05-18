#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include "ExceptionHandler.h"
#include "User.h"
#include "ProcessHandler.h"
#define POST_COMMAND "POST"
#define PUT_COMMAND "PUT"
#define DELETE_COMMAND "DELETE"
#define GET_COMMAND "GET"
#define COMMAND_TYPE_INDEX 0
#define FIRST_PARAM_INDEX 3
#define FUNCTION_INDEX 1
#define HAS_ERROR 1
#define NO_ERROR 0
typedef std::map<std::string,std::string> Map;
typedef std::string input;
typedef unsigned int Counter;
typedef std::vector<std::string> CommandList;
class InputHandler
{
    public:
        InputHandler();
        void start();
    private:
        ProcessHandler handler;
        void handleInput();
        CommandList seperateString(input line);
        void checkSyntaxErrors(CommandList words);
        void commandExists(CommandList words);
        void checkParameters(CommandList words);
        void checkFirstParameter(std::string first_command);
        bool questionMarkExists(CommandList words);
        bool isEven(int number);
        void checkFunctions(CommandList words);
        void checkSignUp(CommandList words);
        void checkLogin(CommandList words);
        void checkSubmitFilm(CommandList words);
        void checkEditFilm(CommandList words);
        void checkDeleteFilm(CommandList words);
        void checkShowFollowers(CommandList words);
        void checkGetMoney(CommandList words);
        void checkPublishedFilms(CommandList words);
        void checkReply(CommandList words);
        void checkDeleteComment(CommandList words);
        void checkFollow(CommandList words);
        void checkChargeAccount(CommandList words);
        void checkSearchMovie(CommandList words);
        void checkMovieDetails(CommandList words);
        void checkBuyFilm(CommandList words);
        void checkRateMovie(CommandList words);
        void checkComment(CommandList words);
        void checkPurchases(CommandList words);
        void checkUnreadNotifications(CommandList words);
        void checkNotifications(CommandList words);
        bool isEmpty(Map words);
};

#endif