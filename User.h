#ifndef USER_H
#define USER_H
#include <string>
#include "ExceptionHandler.h"
#include <map>
typedef std::map<std::string,std::string> Map;
class User
{
    public:
        User(std::string _username,
             std::string _password,
             std::string _email,
             int _age);
        void follow(Map input);
        void chargeAccount(Map input);
        void searchMovies(Map input);
        void viewMovieDetails(Map input);
        void buyMovie(Map input);
        void rateMovie(Map input);
        void postComment(Map input);
        void viewPurchases(Map input);
        void viewUnreadNotifs(Map input);
        void viewNotifs(Map input);
        virtual void submitMovie(Map input);
        virtual void editMovieDetails(Map input);
        virtual void deleteMovie(Map input);
        virtual void viewFollowers(Map input);
        virtual void recieveMoney(Map input);
        virtual void viewMovies(Map input);
        virtual void replyComment(Map input);
        virtual void deleteComments(Map input);
        std::string getUsername() const;
        std::string getPassword() const;
        // std::string getEmail() const;
        // int getAge() const;
        // int getId() const;
        void setId(int _id);
        virtual std::string getType();
    protected:
        std::string username;
        std::string password;
        std::string email;
        int age;
        int id;
        int wallet;
        std::vector<Movie*> purchased_films;
};

#endif