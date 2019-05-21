#include "MovieRepository.h"

MovieRepository::MovieRepository()
{
    last_id = 0;
    wallet = 0;
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

std::vector<Movie*> MovieRepository::copyMovies(std::vector<Movie*> new_database)
{
    for(Counter i=0; i<movies.size(); i++)
        new_database.push_back(movies[i]);
    return new_database;
}

Movie* MovieRepository::findMovie(int film_id)
{
    if(film_id <= 0)
        throw BadRequest();
    for(Counter i=0; i<movies.size(); i++)
        if(movies[i]->getId() == film_id)
            return movies[i];
    throw NotFound();
}

void MovieRepository::increaseMoney(int amount)
{
    wallet += amount;
}

int MovieRepository::calculateShare(int film_id)
{
    int amount_returned = 0;
    for(Counter i=0; i<movies.size(); i++)
    {
        if(movies[i]->getId() == film_id)
        {
            if(movies[i]->getRate() < 5)
                amount_returned = 8 / 10 * movies[i]->getPrice();
            else if(movies[i]->getRate() >= 5 && movies[i]->getRate() < 8)
                amount_returned = 9 / 10 * movies[i]->getPrice();
            else if(movies[i]->getPrice() >= 8)
                amount_returned = 95 / 100 * movies[i]->getPrice();
            wallet -= amount_returned;
            return amount_returned;
        }
    }
}