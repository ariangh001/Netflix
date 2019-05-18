#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "User.h"
#include "Movie.h"
#include <map>
#include <vector>
typedef std::map<std::string,std::string> Map;
class Publisher : public User
{
    public:
        Publisher(std::string _username,
             std::string _password,
             std::string _email,
             int _age);
        virtual std::string getType();
        virtual void submitMovie(Map input);
        // virtual void editMovieDetails(Map input);
        // virtual void deleteMovie(Map input);
        // virtual void viewFollowers(Map input);
        // virtual void recieveMoney(Map input);
        // virtual void viewMovies(Map input);
        // virtual void replyComment(Map input);
        // virtual void deleteComments(Map input);
    private:
        std::vector<Movie*> my_films;
        std::vector<User*> my_followers;
};

#endif