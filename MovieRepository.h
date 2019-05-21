#ifndef MOVIE_REPOSITORY
#define MOVIE_REPOSITORY
#include "Movie.h"
#include "ExceptionHandler.h"
#include <vector>
typedef unsigned int Counter;
class MovieRepository
{
    public:
        MovieRepository();
        void addMovie(Movie* movie);
        void eraseMovie(int movie_id);
        std::vector<Movie*> copyMovies(std::vector<Movie*> new_database);
        Movie* findMovie(int film_id);
        void increaseMoney(int money);
        int calculateShare(int film_id);
    private:
        std::vector<Movie*> movies;
        int last_id;
        int wallet;
};

#endif