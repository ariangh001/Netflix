#include "ProcessHandler.h"

ProcessHandler::ProcessHandler(UsersRepository* users,MovieRepository* movies)
{
    users_repository = users;
    movie_repository = movies;
    User* admin = new User("admin",sha256("admin"),"admin@admin.com",20);
    users_repository->addUser(admin);
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

void ProcessHandler::checkFunctions(std::string function_type, Map input)
{
    checkPermission(function_type);
    checkValues(input);
    if(active_user->getUsername() != "admin")
    {
        if(function_type == "submitFilm")
        {
            active_user->submitMovie(input,movie_repository);
            notificationHandler(input,"submit");
        }
        else if(function_type == "editFilmDetails")
            active_user->editMovieDetails(input,movie_repository);
        else if(function_type == "deleteFilm")
            active_user->deleteMovie(input,movie_repository);
        else if(function_type == "publishedFilms")
            active_user->viewMovies(input);
        else if(function_type == "showFollowers")
            active_user->viewFollowers(input);
        else if(function_type == "getMoney")
            active_user->recieveMoney(input,movie_repository);
        else if(function_type == "reply")
        {
            active_user->replyComment(input,movie_repository);
            notificationHandler(input,"reply");
        }
        else if(function_type == "deleteComment")
            active_user->deleteComments(input,movie_repository);
        else if(function_type == "follow")
        {
            int size = active_user->getFollowingsNumber();
            followHandler(input);
            if(active_user->getFollowingsNumber() != size)
                notificationHandler(input,"follow");
        }
        else if(function_type == "chargeAccount")
            active_user->chargeAccount(input);
        else if(function_type == "searchMovies")
            active_user->searchMovies(input,movie_repository);
        else if(function_type == "viewDetails")
        {
            AI ai= recommendationHandler();
            active_user->viewMovieDetails(input,movie_repository,ai);
        }

        else if(function_type == "buyInput")
            buyHandler(input);
        else if(function_type == "rateMovie")
        {
            active_user->rateMovie(input,movie_repository);
            notificationHandler(input,"rate");
        }
        else if(function_type == "comment")
        {
            active_user->postComment(input,movie_repository);
            notificationHandler(input,"comment");
        }
        else if(function_type == "purchasedMovies")
            active_user->viewPurchases(input,movie_repository);
        else if(function_type == "viewUnreadNotifs")
            active_user->viewUnreadNotifs(input);
        else if(function_type == "viewNotifs")
            active_user->viewNotifs(input);
        else if(function_type == "viewMoney")
            active_user->viewMoney(movie_repository);
        else
            throw PermissionDenied();
    }
    else
    {
        if(function_type == "viewMoney")
            active_user->viewMoney(movie_repository);
        else
            throw PermissionDenied();
    }
}

void ProcessHandler::checkPermission(std::string function_type)
{
    if(function_type == "signup" || function_type == "login")
    {
        if(active_user != NULL)
            throw BadRequest();
    }
    else
        if(active_user == NULL)
            throw PermissionDenied();
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
            if(isNumber(itr->second) == false && itr->second != "-1")
                throw BadRequest();
        if(itr->first == "is_publisher")
            if(itr->second != "true" && itr->second != "false"
            && itr->second != "-1")
                throw BadRequest();
        if(itr->first == "min_rate" && itr->second != "-1")
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

void ProcessHandler::followHandler(Map input)
{
    User* publisher = users_repository->findPublisher(stoi(input["user_id"]));
    active_user->follow(input,publisher);
    publisher->addFollower(active_user);
}

void ProcessHandler::notificationHandler(Map input, std::string function)
{
    if(function == "reply")
        replyNotifHandler(input);
    else if(function == "submit")
        submitNotifHandler(input);
    else if(function == "follow")
        followNotifHandler(input);
    else if(function == "buy")
        buyNotifHandler(input);
    else if(function == "rate")
        rateNotifHandler(input);
    else if(function == "comment")
        commentNotifHandler(input);
}
void ProcessHandler::submitNotifHandler(Map input)
{
    std::string notification = active_user->submitNotification();
    std::vector<User*> followers = active_user->getFollowers();
    for(Counter i=0; i<followers.size(); i++)
        followers[i]->recieveNotification(notification);
}

void ProcessHandler::followNotifHandler(Map input)
{
    std::string notification = active_user->followNotification();
    User* publisher = users_repository->findPublisher(stoi(input["user_id"]));
    publisher->recieveNotification(notification);
}

void ProcessHandler::replyNotifHandler(Map input)
{
    std::string notification = active_user->replyNotification();
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    Comment* comment = movie->findComment(stoi(input["comment_id"]));
    int user_id = comment->getUserId();
    User* user = users_repository->findPeople(user_id);
    user->recieveNotification(notification);
}

void ProcessHandler::commentNotifHandler(Map input)
{
    std::string notification = active_user->commentNotification(movie_repository,input);
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    User* publisher = users_repository->findPublisher(movie->getPubId());
    publisher->recieveNotification(notification);
}

void ProcessHandler::buyNotifHandler(Map input)
{
    std::string notification = active_user->buyNotification(movie_repository,input);
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    User* publisher = users_repository->findPublisher(movie->getPubId());
    publisher->recieveNotification(notification);
}

void ProcessHandler::rateNotifHandler(Map input)
{
    std::string notification = active_user->rateNotification(movie_repository,input);
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    User* publisher = users_repository->findPublisher(movie->getPubId());
    publisher->recieveNotification(notification);
}

void ProcessHandler::buyHandler(Map input)
{
    Movie* movie = movie_repository->findMovie(stoi(input["film_id"]));
    int pub_id = movie->getPubId();
    User* publisher = users_repository->findPublisher(pub_id);
    int size = active_user->getFilmsNumber();
    active_user->buyMovie(input,movie_repository,publisher);
    if(active_user->getFilmsNumber() != size)
        notificationHandler(input,"buy");
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