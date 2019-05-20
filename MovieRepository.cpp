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

void MovieRepository::eraseMovie(int movie_id)
{
    for(Counter i=0; i<movies.size(); i++)
        if(movies[i]->getId() == movie_id)
            movies.erase(movies.begin() + i);
}