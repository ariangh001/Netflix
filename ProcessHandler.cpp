#include "ProcessHandler.h"

ProcessHandler::ProcessHandler()
{
}

void ProcessHandler::signup(Map input)
{
    std::string user_type = "user";
    for(auto itr=input.begin(); itr!=input.end(); ++itr)
        if(itr->first == "is_publisher")
            if(itr->second == "true")
                user_type = "publisher";
    if(user_type == "user")
    {
        User* new_user = new User(
        input["username"],/*hash*/input["password"],
        input["email"],stoi(input["age"]));
        users_repository.addUser(new_user);
        active_user = new_user;
    }
    else if(user_type == "publisher")
    {
        Publisher* new_publisher = new Publisher(
        input["username"],/*hash*/input["password"],
        input["email"],stoi(input["age"]));
        users_repository.addUser(new_publisher);
        active_user = new_publisher;
    }
}

void ProcessHandler::login(Map input)
{
    std::string username, password;
    for(auto itr=input.begin(); itr!=input.end(); itr++)
    {
        if(itr->first == "username")
            username = itr->second;
        else if(itr->first == "password")
            password = itr->second;
    }
    // password = hash(password);
    active_user = users_repository.findUser(username,password);
}

void ProcessHandler::checkFunctions(std::string function_type, Map input)
{
    checkPermission(function_type);
    checkValues(input);
    if(function_type == "submitFilm")
        active_user->submitMovie(input);
    // else if(function_type == "editFilmDetails")
    //     active_user->editMovieDetails(input);
    // else if(function_type == "deleteFilm")
    //     active_user->deleteMovie(input);
    // else if(function_type == "publishedFilms")
    //     active_user->viewMovies(input);
    // else if(function_type == "showFollowers")
    //     active_user->viewFollowers(input);
    // else if(function_type == "getMoney")
    //     active_user->recieveMoney(input);
    // else if(function_type == "reply")
    //     active_user->replyComment(input);
    // else if(function_type == "deleteComment")
    //     active_user->deleteComments(input);
    // else if(function_type == "follow")
    //     active_user->follow(input);
    // else if(function_type == "chargeAccount")
    //     active_user->chargeAccount(input);
    // else if(function_type == "searchMovies")
    //     active_user->searchMovies(input);
    // else if(function_type == "viewDetails")
    //     active_user->viewMovieDetails(input);
    // else if(function_type == "buyInput")
    //     active_user->buyMovie(input);
    // else if(function_type == "rateMovie")
    //     active_user->rateMovie(input);
    // else if(function_type == "comment")
    //     active_user->postComment(input);
    // else if(function_type == "purchasedMovies")
    //     active_user->viewPurchases(input);
    // else if(function_type == "viewUnreadNotifs")
    //     active_user->viewUnreadNotifs(input);
    // else if(function_type == "viewNotifs")
    //     active_user->viewNotifs(input);
}

 void ProcessHandler::checkPermission(std::string function_type)
 {
    if(users_repository.getUsersNumber() == 0)
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
            if(isNumber(itr->second) == false)
                throw BadRequest();
        if(itr->first == "is_publisher")
            if(itr->second != "true" && itr->second != "false"
            && itr->second != "-1")
                throw BadRequest();
        if(itr->first == "director" || itr->first == "name")
            if(isNumber(itr->second) == true)
                throw BadRequest();
        if(itr->first == "min_rate")
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