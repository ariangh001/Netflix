#ifndef MOVIE_REPOSITORY_H
#define MOVIE_REPOSITORY_H
#include "Movie.h"
#include "ExceptionHandler.h"
#include <vector>
typedef unsigned int Counter;
class MovieRepository
{
    public:
        MovieRepository();
        ~MovieRepository();
        void addMovie(Movie* movie);
        void eraseMovie(int movie_id);
        std::vector<Movie*> copyMovies(std::vector<Movie*> new_database);
        Movie* findMovie(int film_id);
        void increaseMoney(int money);
        void decreaseMoney(int money);
        int calculateShare(int film_id);
        std::vector<Movie*> deleteMovies(std::vector<Movie*> temp, Movie* movie);
        Movie* filterByRate(std::vector<Movie*> temp);
    private:
        std::vector<Movie*> movies;
        int last_id;
        int wallet;
};

#endif