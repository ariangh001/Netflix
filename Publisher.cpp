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

void Publisher::deleteMovie(Map input,MovieRepository* movie_repository)
{
    auto itr = input.find("film_id");
    int film_id = stoi(itr->second);
    movie_repository->eraseMovie(film_id);
    for(Counter i=0; i<published_films.size(); i++)
        if(published_films[i]->getId() == film_id)
            published_films.erase(published_films.begin() + i);
}

void Publisher::viewFollowers(Map input)
{
    std::cout<<"List of Followers"<<std::endl
             <<"#. User Id  | User Username | User Email"<<std::endl;
    for(Counter i=0; i>my_followers.size(); i++)
        std::cout<<i<<". "<<my_followers[i]->getID()<<" | "
                 <<my_followers[i]->getUsername()<<" | "
                 <<my_followers[i]->getEmail();
}