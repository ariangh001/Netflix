#include "User.h"

User::User(std::string _username, std::string _password,
            std::string _email, int _age)
{
    username = _username;
    password = _password;
    email = _email;
    if(_age > 0)
        age = _age;
    else
        throw BadRequest();
    wallet = 0;
    id = 0;
}

void User::setId(int _id)
{
    if(_id > 0)
        id = _id;
    else
        throw BadRequest();
}

int User::getId() const
{
    return id;
}

int User::getFilmsNumber() const
{
    return purchased_films.size();
}

int User::getFollowingsNumber() const
{
    return following_ids.size();
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

std::vector<Movie*> User::viewMovies(Map input)
{
    throw PermissionDenied();
}

void User::replyComment(Map input,MovieRepository* repo)
{
    throw PermissionDenied();
}

void User::deleteComments(Map input,MovieRepository* repo)
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

void User::increaseVirtualWallet(int money)
{
    throw PermissionDenied();
}

void User::follow(Map input, User* publisher)
{
    for(Counter i=0;i<following_ids.size();i++)
        if(following_ids[i] == publisher->getId())
            return;
    following_ids.push_back(publisher->getId());
}

void User::chargeAccount(Map input)
{
    int cash = stoi(input["amount"]);
    if(cash >= 0)
        wallet += cash;
    else
        throw BadRequest();
}

std::vector<Movie*> User::showValidMovies(MovieRepository* repo)
{
    std::vector<Movie*> movies , new_movies;
    movies = repo->copyMovies(movies);
    for(Counter i=0; i<movies.size(); i++)
        if(movies[i]->getPrice() <= wallet && movies[i]->isDeleted() == false)
            new_movies.push_back(movies[i]);
    return new_movies;
}

std::vector<Movie*> User::filterMovies(std::vector<Movie*> unfiltered_movies,Map input)
{
    unfiltered_movies = filterDirector(unfiltered_movies,input);
    unfiltered_movies = eraseDeletedMovies(unfiltered_movies);
    return unfiltered_movies;
}

std::vector<Movie*> User::eraseDeletedMovies(std::vector<Movie*> unfiltered_movies)
{
    std::vector<Movie*> filtered_movies;
    for(Counter i=0; i<unfiltered_movies.size(); i++)
        if(unfiltered_movies[i]->isDeleted() == false)
            filtered_movies.push_back(unfiltered_movies[i]);
    return filtered_movies;
}

std::vector<Movie*> User::filterDirector(std::vector<Movie*> unfiltered_movies,Map input)
{
    if(input["director"] != "")
    {
        std::vector<Movie*> filtered_movies;
        for(Counter i=0; i<unfiltered_movies.size(); i++)
            if(unfiltered_movies[i]->getDirector() == input["director"])
                filtered_movies.push_back(unfiltered_movies[i]);
        return filtered_movies;
    }
    return unfiltered_movies;
}

std::vector<Movie*> User::viewMovieDetails(Map input,MovieRepository* repo,AI &ai)
{
    int film_id = stoi(input["film_id"]);
    Movie* movie = repo->findMovie(film_id);
    movie->showCommentsDetails();
    std::vector<Movie*> temp, recommended;
    temp = repo->copyMovies(temp);
    recommended = ai.recommendMovie(film_id,temp,purchased_films);
    return recommended;
}

void User::buyMovie(Map input,MovieRepository* repo,User* publisher)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<purchased_films.size(); i++)
        if(movie->getId() == purchased_films[i]->getId())
            return;
    if(movie->getPrice() <= wallet)
    {
        wallet -= movie->getPrice();
        purchased_films.push_back(movie);
        repo->increaseMoney(movie->getPrice());
        movie->increaseSoldNumbers();
        publisher->increaseVirtualWallet(repo->calculateShare(movie->getId()));
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
            movie->addRate(id,stoi(input["score"]));
            movie->updateRate();
            return;
        }
    throw PermissionDenied();
}

void User::postComment(Map input,MovieRepository* repo)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    for(Counter i=0; i<purchased_films.size(); i++)
        if(movie->getId() == purchased_films[i]->getId())
        {
            Comment* comment = new Comment(input["content"],id,movie->getId());
            movie->addComment(comment);
            return;
        }
    throw PermissionDenied();
}

std::vector<Movie*> User::viewPurchases(Map input,MovieRepository* repo)
{
    std::vector<Movie*> unfiltered_movies;
    for(Counter i=0; i<purchased_films.size(); i++)
        unfiltered_movies.push_back(purchased_films[i]);
    unfiltered_movies = filterDirector(unfiltered_movies,input);
    return unfiltered_movies;
}

std::string User::replyNotification()
{
    std::string content = "Publisher ";
    content += username;
    content += " with id ";
    content += std::to_string(id);
    content += " reply to your comment.";
    return content;
}

std::string User::submitNotification()
{
    std::string content = "Publisher ";
    content += username;
    content += " with id ";
    content += std::to_string(id);
    content += " register new film.";
    return content;
}

std::string User::followNotification()
{
    std::string content = "User ";
    content += username;
    content += " with id ";
    content += std::to_string(id);
    content += " follow you.";
    return content;
}

std::string User::buyNotification(MovieRepository* repo, Map input)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    std::string content = "User ";
    content += username;
    content += " with id ";
    content += std::to_string(id);
    content += " buy your film ";
    content += movie->getName();
    content += " with id ";
    content += input["film_id"];
    content += '.';
    return content;
}

std::string User::rateNotification(MovieRepository* repo, Map input)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    std::string content = "User ";
    content += username;
    content += " with id ";
    content += std::to_string(id);
    content += " rate your film ";
    content += movie->getName();
    content += " with id ";
    content += input["film_id"];
    content += '.';
    return content;
}

std::string User::commentNotification(MovieRepository* repo, Map input)
{
    Movie* movie = repo->findMovie(stoi(input["film_id"]));
    std::string content = "User ";
    content += username;
    content += " with id ";
    content += std::to_string(id);
    content += " comment on your film ";
    content += movie->getName();
    content += " with id ";
    content += input["film_id"];
    content += '.';
    return content;
}

void User::recieveNotification(std::string notif)
{
    unread_notifications.push_back(notif);
}

void User::viewUnreadNotifs(Map input)
{
    std::cout<<"#. Notification Message"<<std::endl;
    for(Counter i =0; i<unread_notifications.size(); i++)
        std::cout<<i + 1<<". "<<unread_notifications[unread_notifications.size() - i - 1]<<std::endl;
    for(Counter i=0; i<unread_notifications.size(); i++)
        read_notifications.push_back(unread_notifications[i]);
    unread_notifications.clear();
}

void User::viewNotifs(Map input)
{
    int last_num = read_notifications.size() - stoi(input["limit"]);
    if(last_num < 0)
        last_num = 0;
    std::cout<<"#. Notification Message"<<std::endl;
    for(Counter i= read_notifications.size() - 1; i >= last_num; i--)
        std::cout<<read_notifications.size() - i<<". "<<read_notifications[i]<<std::endl;
}

std::string User::viewMoney(MovieRepository* repo)
{
    if(username != "admin")
        return std::to_string(wallet);
    else
        return std::to_string(repo->getWallet());
}

std::vector<Movie*> User::getPurchased(std::vector<Movie*> movies)
{
    for(Counter i=0; i<purchased_films.size(); i++)
        movies.push_back(purchased_films[i]);
    return movies;
}

int User::getWallet() const
{
    return wallet;
}