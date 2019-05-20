#include "Publisher.h"

Publisher::Publisher(std::string _username, std::string _password,
                                        std::string _email, int _age)
        :User(_username,_password,_email,_age)
{
}

std::string Publisher::getType()
{
    return "publisher";
}

void Publisher::submitMovie(Map input,MovieRepository* movie_repository)
{
    Movie* new_movie = new Movie(input["name"],stoi(input["year"]),
        stoi(input["length"]),stoi(input["price"]),input["summary"],input["director"],0);
    movie_repository->addMovie(new_movie);
    published_films.push_back(new_movie);
    //send_notif
}

void Publisher::editMovieDetails(Map input,MovieRepository* movie_repository)
{
    if(input["film_id"] == "-1")
    {
        for(Counter i=0; i<published_films.size(); i++)
        {
            if(published_films[i]->getId() == stoi(input["film_id"]))
            {
                if(input["name"] != "-1")
                    published_films[i]->setName(input["name"]);
                else if(input["year"] == "-1")
                    published_films[i]->setYear(stoi(input["year"]));
                else if(input["length"] == "-1")
                    published_films[i]->setLength(stoi(input["length"]));
                else if(input["price"] == "-1")
                    published_films[i]->setPrice(stoi(input["price"]));
                else if(input["summary"] == "-1")
                    published_films[i]->setSummary(input["summary"]);
                else if(input["director"] == "-1")
                    published_films[i]->setDirector(input["director"]);
            }
            break;
        }
    }
}