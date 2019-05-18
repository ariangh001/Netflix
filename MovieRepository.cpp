#include "MovieRepository.h"

MovieRepository::MovieRepository()
{
    last_id = 0;
}

void MovieRepository::addMovie(Movie* movie)
{
    last_id++;
    movie->setId(last_id);
    movies.push_back(movie);
}