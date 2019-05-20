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
