#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "User.h"
#include "Movie.h"
#include "MovieRepository.h"
#include "ExceptionHandler.h"
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
typedef std::map<std::string,std::string> Map;
typedef unsigned int Counter;
class Publisher : public User
{
    public:
        Publisher(std::string _username,
             std::string _password,
             std::string _email,
             int _age);
        virtual std::string getType();
        virtual void submitMovie(Map input,MovieRepository* movie_repository);
        virtual void editMovieDetails(Map input,MovieRepository* movie_repository);
        virtual void deleteMovie(Map input,MovieRepository* movie_repository);
        virtual void viewFollowers(Map input);
        virtual void addFollower(User* user);
        virtual void recieveMoney(Map input,MovieRepository* repo);
        virtual void viewMovies(Map input);
        virtual void replyComment(Map input,MovieRepository* repo);
        virtual void deleteComments(Map input,MovieRepository* repo);
        virtual std::vector<User*> getFollowers();
        virtual void increaseVirtualWallet(int money);
    private:
        std::vector<Movie*> published_films;
        std::vector<User*> my_followers;
        int virtual_wallet;
};

#endif