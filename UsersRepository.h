#ifndef USERS_REPOSITORY_H
#define USERS_REPOSITORY_H
#include "User.h"
#include "ExceptionHandler.h"
#include <vector>
#include <iostream>
typedef unsigned int Counter;
class UsersRepository
{
    public:
        void addUser(User* new_user);
        User* findUser(std::string username, std::string password);
        int getUsersNumber();
    private:
        std::vector<User*> users;
};
#endif