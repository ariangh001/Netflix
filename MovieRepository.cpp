#include "MovieRepository.h"

MovieRepository::MovieRepository()
{
    last_id = 0;
    wallet = 0;
}

MovieRepository::~MovieRepository()
{
    for(Counter i=0; i< movies.size(); i++)
        delete movies[i];
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
        {
            movies[i]->deleteMovie();
            return;
        }
    throw NotFound();
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
        if(movies[i]->getId() == film_id && movies[i]->isDeleted() == false)
            return movies[i];
    throw NotFound();
}

void MovieRepository::increaseMoney(int amount)
{
    if(amount >= 0)
        wallet += amount;
    else
        throw BadRequest();
}

int MovieRepository::calculateShare(int film_id)
{
    int amount_returned = 0;
    for(Counter i=0; i<movies.size(); i++)
    {
        if(movies[i]->getId() == film_id)
        {
            if(movies[i]->getRate() < 5)
                amount_returned = (float)8 / 10 * movies[i]->getPrice();
            else if(movies[i]->getRate() >= 5 && movies[i]->getRate() < 8)
                amount_returned = (float)9 / 10 * movies[i]->getPrice();
            else if(movies[i]->getPrice() >= 8)
                amount_returned = (float)95 / 100 * movies[i]->getPrice();
            return amount_returned;
        }
    }
    throw NotFound();
}

void MovieRepository::decreaseMoney(int money)
{
    if(money >= 0)
        wallet -= money;
    else
        throw BadRequest();
}

std::vector<Movie*> MovieRepository::deleteMovies(std::vector<Movie*> temp, Movie* movie)
{
    for(Counter i=0; i<temp.size(); i++)
        if(temp[i]->getId() == movie->getId())
            temp.erase(temp.begin() + i);
    return temp;
}

Movie* MovieRepository::filterByRate(std::vector<Movie*> temp)
{
    Movie* temp_movie = temp[0];
    for(Counter i=0; i<temp.size(); i++)
        if(temp[i]->getRate() > temp_movie->getRate())
            temp_movie = temp[i];
    return temp_movie;
}

int MovieRepository::getWallet() const
{
    return wallet;
}