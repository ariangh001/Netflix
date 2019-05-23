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
        stoi(input["length"]),stoi(input["price"]),input["summary"],input["director"],0,id);
    movie_repository->addMovie(new_movie);
    published_films.push_back(new_movie);
    std::cout<<OK_REQUEST<<std::endl;
}

void Publisher::editMovieDetails(Map input,MovieRepository* movie_repository)
{
    if(input["film_id"] != "-1")
    {
        for(Counter i=0; i<published_films.size(); i++)
        {
            if(published_films[i]->getId() == stoi(input["film_id"]))
            {
                if(input["name"] != "-1")
                    published_films[i]->setName(input["name"]);
                else if(input["year"] != "-1")
                    published_films[i]->setYear(stoi(input["year"]));
                else if(input["length"] != "-1")
                    published_films[i]->setLength(stoi(input["length"]));
                else if(input["price"] != "-1")
                    published_films[i]->setPrice(stoi(input["price"]));
                else if(input["summary"] != "-1")
                    published_films[i]->setSummary(input["summary"]);
                else if(input["director"] != "-1")
                    published_films[i]->setDirector(input["director"]);
            }
            break;
        }
    }
    else
    {
        if(!(input["name"] == "-1" && input["length"] == "-1"
        &&   input["year"] == "-1" && input["price"] == "-1"
        &&   input["summary"] == "-1" && input["director"] == "-1"))
            throw BadRequest();
    }
    std::cout<<OK_REQUEST<<std::endl;
}

void Publisher::deleteMovie(Map input,MovieRepository* movie_repository)
{
    auto itr = input.find("film_id");
    int film_id = stoi(itr->second);
    for(Counter i=0; i<published_films.size(); i++)
        if(published_films[i]->getId() == film_id)
        {
            movie_repository->eraseMovie(film_id);
            published_films.erase(published_films.begin() + i);
            std::cout<<OK_REQUEST<<std::endl;
            return;
        }
    throw PermissionDenied();
}

void Publisher::viewFollowers(Map input)
{
    std::cout<<"List of Followers"<<std::endl
             <<"#. User Id  | User Username | User Email"<<std::endl;
    for(Counter i=0; i>my_followers.size(); i++)
        std::cout<<i+1<<". "<<my_followers[i]->getId()<<" | "
                 <<my_followers[i]->getUsername()<<" | "
                 <<my_followers[i]->getEmail();
}

void Publisher::viewMovies(Map input)
{
    std::cout<<"#. Film Id | Film Name | Film Length"
    <<" | Film price | Rate | Production Year | Film Director"<<std::endl;
    for(Counter i=0; i<published_films.size(); i++)
    {
        std::cout<<i+1<<". "<<published_films[i]->getId()<<" | "
        <<published_films[i]->getName()<<" | "
        <<published_films[i]->getLength()<<" | "
        <<published_films[i]->getPrice()<<" | ";
        std::cout<<std::setprecision(2)<<published_films[i]->getRate()<<" | ";
        std::cout<<published_films[i]->getYear()<<" | "
        <<published_films[i]->getDirector()<<std::endl;
    }
}

void Publisher::addFollower(User* user)
{
    my_followers.push_back(user);
}

void Publisher::recieveMoney(Map input,MovieRepository* repo)
{
    for(Counter i=0; i<published_films.size(); i++)
        wallet += repo->calculateShare(published_films[i]->getId());
    std::cout<<OK_REQUEST<<std::endl;
}

void Publisher::replyComment(Map input,MovieRepository* repo)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<published_films.size(); i++)
        if(published_films[i]->getId() == movie->getId())
        {
            Comment* comment = movie->findComment(stoi(input["comment_id"]));
            if(comment->getId() == stoi(input["comment_id"]))
            {
                Reply* reply = new Reply(
                    stoi(input["comment_id"]),id,movie->getId(),addSpaces(input["content"]));
                movie->addReply(reply);
                std::cout<<OK_REQUEST<<std::endl;
                return;
            }
        }
    throw PermissionDenied();
}

void Publisher::deleteComments(Map input,MovieRepository* repo)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<published_films.size(); i++)
        if(published_films[i]->getId() == movie->getId())
        {
            Comment* comment = movie->findComment(stoi(input["comment_id"]));
            if(comment->getId() == stoi(input["comment_id"]))
            {
                movie->deleteComment(stoi(input["comment_id"]));
                std::cout<<OK_REQUEST<<std::endl;
                return;
            }
        }
    throw PermissionDenied();
}

std::vector<User*> Publisher::getFollowers()
{
    return my_followers;
}