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
        std::vector<Movie*> viewPurchases(Map input,std::string session_id);
        std::vector<Movie*> viewPublishes(Map input,std::string session_id);
        Movie* searchMovie(int film_id, std::string session_id);
        void submitMovie(Map input,std::string session_id);
        void editFilmDetails(Map input,std::string session_id);
        void deleteFilm(Map input,std::string session_id);
        void showFollowers(Map input,std::string session_id);
        void getMoney(Map input,std::string session_id);
        void reply(Map input,std::string session_id);
        void deleteComment(Map input,std::string session_id);
        void follow(Map input,std::string session_id);
        void chargeAccount(Map input,std::string session_id);
        std::vector<Movie*> showValidMovies(std::string session_id);
        std::vector<Movie*> viewDetails(Map input,std::string session_id);
        std::vector<Comment*> viewComments(int film_id, std::string session_id);
        void buy(Map input,std::string session_id);
        void rateMovie(Map input,std::string session_id);
        void postComment(Map input,std::string session_id);
        void viewUnreadNotifications(Map input,std::string session_id);
        void viewNotifications(Map input,std::string session_id);
        std::string viewMoney(Map input,std::string session_id);
        void checkInput(Map input,std::string function_type);
        void checkPermission(std::string session_id);
        void followHandler(Map input,std::string session_id);
        void notificationHandler(Map input,std::string function,std::string session_id);
        void submitNotifHandler(Map input,std::string session_id);
        void followNotifHandler(Map input,std::string session_id);
        void replyNotifHandler(Map input,std::string session_id);
        void commentNotifHandler(Map input,std::string session_id);
        void buyNotifHandler(Map input,std::string session_id);
        void rateNotifHandler(Map input,std::string session_id);
        void buyHandler(Map input,std::string session_id);
        AI recommendationHandler();
        bool isPublisher(std::string session_id);
        bool compareMoney(std::string session_id, int money);
        bool hasPurchased(std::string session_id, int id);
        void setMovieId(int id);
        int getLastId() const;
    private:
        Active active_users;
        MovieRepository* movie_repository;
        UsersRepository* users_repository;
        void checkValues(Map input);
        bool isEmpty(Map words);
        bool isNumber(std::string str);
        bool isFloat(std::string str);
        void checkEmailSyntax(std::string email);
        int last_movie_id;
};
#endif