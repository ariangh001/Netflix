#ifndef MOVIE_REPOSITORY
#define MOVIE_REPOSITORY
#include "Movie.h"
#include <vector>

class MovieRepository
{
    public:
        MovieRepository();
        void addMovie();//check kardane user id e jadid
        //new kardan too khode add anjam beshe bekhatere check kardane id ba ozve akhare vector
        //va new kardan ba tavajoh be oon anjam mishe
    private:
        std::vector<Movie*> movies;
        int last_id;
};

#endif