#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "ExceptionHandler.h"
#include "MovieRepository.h"
#include <map>
#include "Movie.h"
#include <vector>
typedef unsigned int Counter;
typedef std::map<std::string,std::string> Map;
class User
{
    public:
        User(std::string _username,
             std::string _password,
             std::string _email,
             int _age);
        void follow(Map input,User* publisher);
        void chargeAccount(Map input);
        void searchMovies(Map input,MovieRepository* repo);
        std::vector<Movie*> filterMovies(std::vector<Movie*> unfiltered_movies,Map input);
        std::vector<Movie*> filterName(std::vector<Movie*> unfiltered_movies,Map input);
        std::vector<Movie*> filterPrice(std::vector<Movie*> unfiltered_movies,Map input);
        std::vector<Movie*> filterYear(std::vector<Movie*> unfiltered_movies,Map input);
        std::vector<Movie*> filterDirector(std::vector<Movie*> unfiltered_movies,Map input);
        std::vector<Movie*> filterRate(std::vector<Movie*> unfiltered_movies,Map input);
        void viewMovieDetails(Map input,MovieRepository* repo);
        void buyMovie(Map input,MovieRepository* repo);
        void rateMovie(Map input);
        void postComment(Map input);
        void viewPurchases(Map input);
        void viewUnreadNotifs(Map input);
        void viewNotifs(Map input);
        void sendNotification();
        virtual void submitMovie(Map input);
        virtual void editMovieDetails(Map input);
        virtual void deleteMovie(Map input);
        virtual void viewFollowers(Map input);
        virtual void recieveMoney(Map input);
        virtual void viewMovies(Map input);
        virtual void replyComment(Map input);
        virtual void deleteComments(Map input);
        virtual void addFollower(User* user);
        std::string getUsername() const;
        std::string getPassword() const;
        std::string getEmail() const;
        // int getAge() const;
        int getId() const;
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
        std::vector<int> following_ids;
};

#endif