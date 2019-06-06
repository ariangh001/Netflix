#include "ProcessHandler.h"

ProcessHandler::ProcessHandler(UsersRepository* users,MovieRepository* movies)
{
    users_repository = users;
    movie_repository = movies;
    User* admin = new User("admin",sha256("admin"),"admin@admin.com",20);
    users_repository->addUser(admin);
    last_movie_id = 0;
}

void ProcessHandler::checkInput(Map input,std::string function_type)
{
    checkValues(input);
    if(function_type == "signup")
        checkEmailSyntax(input["email"]);
    else if(function_type == "login" || function_type == "submitMovie"
          ||function_type == "deleteFilms" || function_type == "deleteComments"
          ||function_type == "follow" || function_type == "charge"
          ||function_type == "viewDetails" || function_type == "buy"
          ||function_type == "rate" || function_type == "comment"
          ||function_type == "notifications" || function_type == "signup")
        if(isEmpty(input) == true)
            throw BadRequest();
}

std::string ProcessHandler::signup(Map input,std::string function_type)
{
    std::string user_type = "user";
    for(auto itr=input.begin(); itr!=input.end(); ++itr)
        if(itr->first == "is_publisher")
            if(itr->second == "true")
                user_type = "publisher";
    if(user_type == "user")
    {
        User* new_user = new User(
        input["username"],sha256(input["password"]),
        input["email"],stoi(input["age"]));
        users_repository->addUser(new_user);
        active_users.insert({sha256(std::to_string(new_user->getId())),new_user});
        return sha256(std::to_string(new_user->getId()));
    }
    else if(user_type == "publisher")
    {
        Publisher* new_publisher = new Publisher(
        input["username"],sha256(input["password"]),
        input["email"],stoi(input["age"]));
        users_repository->addUser(new_publisher);
        active_users.insert({sha256(std::to_string(new_publisher->getId())),new_publisher});
        return sha256(std::to_string(new_publisher->getId()));
    }
}

std::string ProcessHandler::login(Map input,std::string function_type)
{
    std::string username, password;
    for(auto itr=input.begin(); itr!=input.end(); itr++)
    {
        if(itr->first == "username")
            username = itr->second;
        else if(itr->first == "password")
            password = itr->second;
    }
    password = sha256(password);
    User* user = users_repository->findUser(username,password);
    active_users.insert({sha256(std::to_string(user->getId())),user});
    return sha256(std::to_string(user->getId()));
}

void ProcessHandler::logout(std::string session_id)
{
    auto itr = active_users.find(session_id);
    if(itr == active_users.end())
        throw BadRequest();
    else
        active_users.erase(session_id);
}

std::vector<Movie*> ProcessHandler::viewPurchases(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    return active_user->viewPurchases(input,movie_repository);
}

std::vector<Movie*> ProcessHandler::viewPublishes(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    return active_user->viewMovies(input);
}

void ProcessHandler::submitMovie(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->submitMovie(input,movie_repository);
    notificationHandler(input,"submit",session_id);
}

void ProcessHandler::editFilmDetails(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->editMovieDetails(input,movie_repository);
}

void ProcessHandler::deleteFilm(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->deleteMovie(input,movie_repository);
}

void ProcessHandler::showFollowers(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->viewFollowers(input);
}

void ProcessHandler::getMoney(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->recieveMoney(input,movie_repository);
}

void ProcessHandler::reply(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->replyComment(input,movie_repository);
    notificationHandler(input,"reply",session_id);
}

void ProcessHandler::deleteComment(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->deleteComments(input,movie_repository);
}

void ProcessHandler::follow(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    int size = active_user->getFollowingsNumber();
    followHandler(input,session_id);
    if(active_user->getFollowingsNumber() != size)
        notificationHandler(input,"follow",session_id);
}

void ProcessHandler::chargeAccount(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->chargeAccount(input);
}

std::vector<Movie*> ProcessHandler::showValidMovies(std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    std::vector<Movie*> movies = active_user->showValidMovies(movie_repository);
    return movies;
}

bool ProcessHandler::compareMoney(std::string session_id, int money)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    if(active_user->getWallet() >= money)
        return true;
    return false;
}

bool ProcessHandler::hasPurchased(std::string session_id, int id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    std::vector<Movie*> movies;
    movies = active_user->getPurchased(movies);
    for(Counter i=0; i<movies.size(); i++)
        if(movies[i]->getId() == id)
            return true;
    return false;
}

std::vector<Movie*> ProcessHandler::viewDetails(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    AI ai= recommendationHandler();
    return active_user->viewMovieDetails(input,movie_repository,ai);
}

void ProcessHandler::buy(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    buyHandler(input,session_id);
}

void ProcessHandler::rateMovie(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->rateMovie(input,movie_repository);
    notificationHandler(input,"rate",session_id);
}

void ProcessHandler::postComment(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->postComment(input,movie_repository);
    notificationHandler(input,"comment",session_id);
}

std::vector<Comment*> ProcessHandler::viewComments(int film_id, std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    Movie* movie = movie_repository->findMovie(film_id);
    return movie->showCommentsDetails();
}

void ProcessHandler::viewUnreadNotifications(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->viewUnreadNotifs(input);
}

void ProcessHandler::viewNotifications(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    active_user->viewNotifs(input);
}

std::string ProcessHandler::viewMoney(Map input,std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    return active_user->viewMoney(movie_repository);
}

Movie* ProcessHandler::searchMovie(int film_id, std::string session_id)
{
    checkPermission(session_id);
    User* active_user = active_users[session_id];
    if(active_user->getUsername() == "admin")
        throw PermissionDenied();
    Movie* movie = movie_repository->findMovie(film_id);
    return movie;
}

void ProcessHandler::checkPermission(std::string session_id)
{
    auto itr = active_users.find(session_id);
    if(itr == active_users.end())
        throw PermissionDenied();
}

void ProcessHandler::followHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    User* publisher = users_repository->findPublisher(stoi(input["user_id"]));
    active_user->follow(input,publisher);
    publisher->addFollower(active_user);
}

void ProcessHandler::notificationHandler(Map input, std::string function,std::string session_id)
{
    if(function == "reply")
        replyNotifHandler(input,session_id);
    else if(function == "submit")
        submitNotifHandler(input,session_id);
    else if(function == "follow")
        followNotifHandler(input,session_id);
    else if(function == "buy")
        buyNotifHandler(input,session_id);
    else if(function == "rate")
        rateNotifHandler(input,session_id);
    else if(function == "comment")
        commentNotifHandler(input,session_id);
}

void ProcessHandler::submitNotifHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    std::string notification = active_user->submitNotification();
    std::vector<User*> followers = active_user->getFollowers();
    for(Counter i=0; i<followers.size(); i++)
        followers[i]->recieveNotification(notification);
}

void ProcessHandler::followNotifHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    std::string notification = active_user->followNotification();
    User* publisher = users_repository->findPublisher(stoi(input["user_id"]));
    publisher->recieveNotification(notification);
}

void ProcessHandler::replyNotifHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    std::string notification = active_user->replyNotification();
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    Comment* comment = movie->findComment(stoi(input["comment_id"]));
    int user_id = comment->getUserId();
    User* user = users_repository->findPeople(user_id);
    user->recieveNotification(notification);
}

void ProcessHandler::commentNotifHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    std::string notification = active_user->commentNotification(movie_repository,input);
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    User* publisher = users_repository->findPublisher(movie->getPubId());
    publisher->recieveNotification(notification);
}

void ProcessHandler::buyNotifHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    std::string notification = active_user->buyNotification(movie_repository,input);
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    User* publisher = users_repository->findPublisher(movie->getPubId());
    publisher->recieveNotification(notification);
}

void ProcessHandler::rateNotifHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    std::string notification = active_user->rateNotification(movie_repository,input);
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    User* publisher = users_repository->findPublisher(movie->getPubId());
    publisher->recieveNotification(notification);
}

void ProcessHandler::buyHandler(Map input,std::string session_id)
{
    User* active_user = active_users[session_id];
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    int pub_id = movie->getPubId();
    User* publisher = users_repository->findPublisher(pub_id);
    int size = active_user->getFilmsNumber();
    active_user->buyMovie(input,movie_repository,publisher);
    if(active_user->getFilmsNumber() != size)
        notificationHandler(input,"buy",session_id);
}

AI ProcessHandler::recommendationHandler()
{
    AI ai;
    std::vector<Movie*> movies;
    std::vector<User*> temp;
    movies = movie_repository->copyMovies(movies);
    ai.makeMatrix(movies);
    int first_index,second_index;
    temp = users_repository->copyUsers(temp);
    for(Counter i=1; i<temp.size(); i++)
    {
        std::vector<Movie*> purchases;
        purchases = temp[i]->getPurchased(purchases);
        for(Counter j=0; j<purchases.size(); j++)
        {
            first_index = movie_repository->getIndex(purchases[j]);
            for(Counter k=0; k<purchases.size(); k++)
                if(j != k)
                {
                    second_index = movie_repository->getIndex(purchases[k]);
                    ai.updateMatrix(first_index,second_index);
                }
        }
    }
    return ai;
}


void ProcessHandler::checkValues(Map input)
{
    for(auto itr=input.begin(); itr!=input.end(); itr++)
    {
        if(itr->first == "email")
            checkEmailSyntax(itr->second);
        if(itr->first == "age" || itr->first == "year"
        || itr->first == "price" || itr->first == "length"
        || itr->first == "film_id" || itr->first == "min_year"
        || itr->first == "max_year" || itr->first == "comment_id"
        || itr->first == "user_id" || itr->first == "amount"
        || itr->first == "score" || itr->first == "limit")
            if(isNumber(itr->second) == false && itr->second != "")
                throw BadRequest();
        if(itr->first == "is_publisher")
            if(itr->second != "true" && itr->second != "false"
            && itr->second != "")
                throw BadRequest();
        if(itr->first == "min_rate" && itr->second != "")
            if(isFloat(itr->second) == false)
                throw BadRequest();
    }
}

void ProcessHandler::checkEmailSyntax(std::string email)
{
    int has_error = HAS_ERROR;
    for(Counter i=1; i<email.length(); i++)
    {
        if(email[i] == '@')
        {
            for(Counter j=i+1; j<email.length(); j++)
            {
                if(email[j] == '.' && j != email.length() - 1)
                {
                    has_error = NO_ERROR;
                }
            }
        }
    }
    if(has_error == HAS_ERROR)
        throw BadRequest();
}

bool ProcessHandler::isNumber(std::string str)
{
    for(Counter i=0; i<str.size(); i++)
        if(str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

bool ProcessHandler::isFloat(std::string str)
{
    for(Counter i=0; i<str.size(); i++)
        if((str[i] >= '0' && str[i] <= '9')
        || (str[i] == '.' && (i > 0 && i < str.size()-1)))
            return true;
    return false;
}

bool ProcessHandler::isEmpty(Map words)
{
    for(auto itr = words.begin(); itr != words.end(); itr++)
        if(itr->first != "is_publisher")
            if(itr->second == "")
                throw BadRequest();
}

bool ProcessHandler::isPublisher(std::string session_id)
{
    auto itr = active_users.find(session_id);
    if(itr != active_users.end())
        if(active_users[session_id]->getType() == "publisher")
            return true;
        else
            return false;
    throw NotFound();
}

void ProcessHandler::setMovieId(int id)
{
    if(id > 0)
        last_movie_id = id;
    else
        throw BadRequest();
}

int ProcessHandler::getLastId() const
{
    return last_movie_id;
}