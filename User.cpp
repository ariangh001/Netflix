#include "User.h"

User::User(std::string _username, std::string _password,
            std::string _email, int _age)
{
    username = _username;
    password = _password;
    email = _email;
    age = _age;
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

void User::submitMovie(Map input)
{
    throw PermissionDenied();
}

void User::editMovieDetails(Map input)
{
    throw PermissionDenied();
}

void User::deleteMovie(Map input)
{
    throw PermissionDenied();
}

void User::viewFollowers(Map input)
{
    throw PermissionDenied();
}

void User::recieveMoney(Map input)
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

void User::follow(Map input, UsersRepository* repo)
{
    User* publisher = repo->findPublisher(stoi(input["user_id"]));
    following_ids.push_back(publisher->getId());
}