#include "User.h"

User::User(std::string _username, std::string _password,
            std::string _email, int _age)
{
    username = _username;
    password = _password;
    email = _email;
    age = _age;
    wallet = 0;
}

void User::setId(int _id)
{
    id = _id;
}

int User::getId() const
{
    return id;
}

std::string User::getEmail() const
{
    return email;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

std::string User::getType()
{
    return "user";
}

void User::submitMovie(Map input,MovieRepository* repo)
{
    throw PermissionDenied();
}

void User::editMovieDetails(Map input,MovieRepository* repo)
{
    throw PermissionDenied();
}

void User::deleteMovie(Map input,MovieRepository* repo)
{
    throw PermissionDenied();
}

void User::viewFollowers(Map input)
{
    throw PermissionDenied();
}

void User::recieveMoney(Map input,MovieRepository* repo)
{
    throw PermissionDenied();
}

void User::viewMovies(Map input)
{
    throw PermissionDenied();
}

void User::replyComment(Map input)
{
    throw PermissionDenied();
}

void User::deleteComments(Map input)
{
    throw PermissionDenied();
}

void User::addFollower(User* user)
{
    throw PermissionDenied();
}

std::vector<User*> User::getFollowers()
{
    throw PermissionDenied();
}

void User::follow(Map input, User* publisher)
{
    following_ids.push_back(publisher->getId());
}

void User::chargeAccount(Map input)
{
    int cash = stoi(input["amount"]);
    if(cash > 0)
        wallet += cash;
    else
        throw BadRequest();
}

void User::searchMovies(Map input,MovieRepository* repo)
{
    std::vector<Movie*> unfiltered_movies = repo->copyMovies(unfiltered_movies);
    unfiltered_movies = filterMovies(unfiltered_movies,input);
    std::cout<<"#. Film Id | Film Name | Film Length"
    <<" | Film price | Rate | Production Year | Film Director"<<std::endl;
    for(Counter i=0; i<unfiltered_movies.size(); i++)
    {
        std::cout<<i+1<<". "<<unfiltered_movies[i]->getId()<<" | "
        <<unfiltered_movies[i]->getName()<<" | "
        <<unfiltered_movies[i]->getLength()<<" | "
        <<unfiltered_movies[i]->getPrice()<<" | ";
        std::cout<<std::setprecision(2)<<unfiltered_movies[i]->getRate()<<" | ";
        std::cout<<unfiltered_movies[i]->getYear()<<" | "
        <<unfiltered_movies[i]->getDirector()<<std::endl;
    }
}

std::vector<Movie*> User::filterMovies(std::vector<Movie*> unfiltered_movies,Map input)
{
    unfiltered_movies = filterName(unfiltered_movies,input);
    unfiltered_movies = filterRate(unfiltered_movies,input);
    unfiltered_movies = filterYear(unfiltered_movies,input);
    unfiltered_movies = filterPrice(unfiltered_movies,input);
    unfiltered_movies = filterDirector(unfiltered_movies,input);
    return unfiltered_movies;
}

std::vector<Movie*> User::filterName(std::vector<Movie*> unfiltered_movies,Map input)
{
    if(input["name"] != "-1")
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getName() != input["name"])
                unfiltered_movies.erase(unfiltered_movies.begin() + i);
    return unfiltered_movies;
}

std::vector<Movie*> User::filterPrice(std::vector<Movie*> unfiltered_movies,Map input)
{
    if(input["price"] != "-1")
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getPrice() < stoi(input["price"]))
                unfiltered_movies.erase(unfiltered_movies.begin() + i);
    return unfiltered_movies;
}

std::vector<Movie*> User::filterYear(std::vector<Movie*> unfiltered_movies,Map input)
{
    if(input["min_year"] != "-1")
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getYear() < stoi(input["min_year"]))
                unfiltered_movies.erase(unfiltered_movies.begin() + i);
    if(input["max_year"] != "-1")
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getYear() > stoi(input["max_year"]))
                unfiltered_movies.erase(unfiltered_movies.begin() + i);
    return unfiltered_movies;
}

std::vector<Movie*> User::filterDirector(std::vector<Movie*> unfiltered_movies,Map input)
{
    if(input["director"] != "-1")
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getDirector() != input["director"])
                unfiltered_movies.erase(unfiltered_movies.begin() + i);
    return unfiltered_movies;
}

std::vector<Movie*> User::filterRate(std::vector<Movie*> unfiltered_movies,Map input)
{
    if(input["min_rate"] != "-1")
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getRate() < stoi(input["min_rate"]))
                unfiltered_movies.erase(unfiltered_movies.begin() + i);
    return unfiltered_movies;
}

void User::viewMovieDetails(Map input,MovieRepository* repo)
{
    int film_id = stoi(input["film_id"]);
    Movie* movie = repo->findMovie(film_id);
    std::cout<<"Details of Film "<<movie->getName()<<std::endl
             <<"Id = "<<movie->getId()<<std::endl
             <<"Director = "<<movie->getDirector()<<std::endl
             <<"Length = "<<movie->getLength()<<std::endl
             <<"Year = "<<movie->getYear()<<std::endl
             <<"Summary = "<<movie->getSummary()<<std::endl;
    std::cout<<"Rate = "<<std::setprecision(2)<<movie->getRate()<<std::endl;
    std::cout<<"Price = "<<movie->getPrice()<<std::endl<<std::endl<<std::endl;
    std::cout<<"Comments"<<std::endl;
    movie->showCommentsDetails();
    std::cout<<std::endl<<"Recommendation Film"<<std::endl;
    std::cout<<"#. Film Id | Film Name | Film Length | Film Director"<<std::endl;
    std::vector<Movie*> temp = repo->copyMovies(temp);
    for(Counter i=0; i<purchased_films.size(); i++)
        repo->deleteMovies(temp,purchased_films[i]);
    repo->deleteMovies(temp,movie);
    for(Counter i=0; i<4; i++)
    {
        if(temp.size() == 0)
            break;
        Movie* temp_movie = repo->filterByRate(temp);
        repo->deleteMovies(temp,temp_movie);
        std::cout<<i+1<<". "<<temp_movie->getId()
                 <<" | "<<temp_movie->getName()
                 <<" | "<<temp_movie->getLength()
                 <<" | "<<temp_movie->getDirector()<<std::endl;
    }
}

void User::buyMovie(Map input,MovieRepository* repo)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<purchased_films.size(); i++)
        if(movie->getId() == purchased_films[i]->getId())
        {
            std::cout<<"OK"<<std::endl;
            return;
        }
    if(movie->getPrice() <= wallet)
    {
        wallet -= movie->getPrice();
        purchased_films.push_back(movie);
        movie->increaseSoldNumber();
        repo->increaseMoney(movie->getPrice());
    }
    else
        throw PermissionDenied();
}

void User::rateMovie(Map input,MovieRepository* repo)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<purchased_films.size(); i++)
        if(movie->getId() == purchased_films[i]->getId())
        {
            movie->addRate(id,stoi(input["rate"]));
            movie->updateRate();
            return;
        }
    throw PermissionDenied();
}

std::string User::addSpaces(std::string _string)
{
    for(Counter i=0; i<_string.size(); i++)
        if(_string[i] == '|')
            _string[i] = ' ';
    return _string;
}

void User::postComment(Map input,MovieRepository* repo)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<purchased_films.size(); i++)
        if(movie->getId() == purchased_films[i]->getId())
        {
            Comment* comment = new Comment(addSpaces(input["content"]),id,movie->getId());
            movie->addComment(comment);
            std::cout<<OK_REQUEST<<std::endl;
            return;
        }
    throw PermissionDenied();
}

void User::viewPurchases(Map input,MovieRepository* repo)
{
    std::vector<Movie*> unfiltered_movies;
    for(Counter i=0; i<purchased_films.size(); i++)
        unfiltered_movies.push_back(purchased_films[i]);
    unfiltered_movies  = filterMovies(unfiltered_movies,input);
    std::cout<<"#. Film Id | Film Name | Film Length"
    <<" | Film price | Rate | Production Year | Film Director"<<std::endl;
    for(Counter i=0; i<unfiltered_movies.size(); i++)
    {
        std::cout<<i+1<<". "<<unfiltered_movies[i]->getId()<<" | "
        <<unfiltered_movies[i]->getName()<<" | "
        <<unfiltered_movies[i]->getLength()<<" | "
        <<unfiltered_movies[i]->getPrice()<<" | ";
        std::cout<<std::setprecision(2)<<unfiltered_movies[i]->getRate()<<" | ";
        std::cout<<unfiltered_movies[i]->getYear()<<" | "
        <<unfiltered_movies[i]->getDirector()<<std::endl;
    }
}

std::string User::replyNotification()
{
    std::string content = "Publisher ";
    content += username;
    content += " with id ";
    content += id;
    content += " reply to your comment.";
    return content;
}

std::string User::submitNotification()
{
    std::string content = "Publisher ";
    content += username;
    content += " with id ";
    content += id;
    content += " register new film.";
    return content;
}

std::string User::followNotification()
{
    std::string content = "User ";
    content += username;
    content += " with id ";
    content += id;
    content += " follow you.";
    return content;
}

std::string User::buyNotification(MovieRepository* repo, Map input)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    std::string content = "";
    content += username;
    content += " with id ";
    content += id;
    content += " buy your film ";
    content += movie->getName();
    content += " with id ";
    content += input["film_id"];
    return content;
}

std::string User::rateNotification(MovieRepository* repo, Map input)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    std::string content = "";
    content += username;
    content += " with id ";
    content += id;
    content += " rate your film ";
    content += movie->getName();
    content += " with id ";
    content += input["film_id"];
    return content;
}

std::string User::commentNotification(MovieRepository* repo, Map input)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    std::string content = "";
    content += username;
    content += " with id ";
    content += id;
    content += " comment on your film ";
    content += movie->getName();
    content += " with id ";
    content += input["film_id"];
    return content;
}

void User::recieveNotification(std::string notif)
{
    unread_notifications.push_back(notif);
}

void User::viewUnreadNotifs(Map input)
{
    std::cout<<"#. Notification Message"<<std::endl;
    for(Counter i=unread_notifications.size() - 1; i>=0; i++)
        std::cout<<i+1<<". "<<unread_notifications[i]<<std::endl;
    for(Counter i=0; i<unread_notifications.size(); i++)
        read_notifications.push_back(unread_notifications[i]);
    unread_notifications.clear();
}

void User::viewNotifs(Map input)
{
    std::cout<<"#. Notification Message"<<std::endl;
    for(Counter i=read_notifications.size() - 1; i>=0; i++)
        std::cout<<i+1<<". "<<read_notifications[i]<<std::endl;
}