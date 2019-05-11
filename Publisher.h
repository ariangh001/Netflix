#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "User.h"
#include "Movie.h"
#include <vector>
class Publisher : public User
{
    public:
        Publisher();
        void submitMovie();
        void editMovieDetails();
        void deleteMovie();
        void viewFollowers();
        void recieveMoney();
        void viewMovies();
        void replyComment();
        void deleteComments();
    private:
        std::vector<Movie*> my_films;
        std::vector<User*> my_followers;
};

#endif