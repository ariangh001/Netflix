#ifndef USERS_REPOSITORY_H
#define USERS_REPOSITORY_H
#include "User.h"
#include "ExceptionHandler.h"
#include <vector>
#include <iostream>
typedef unsigned int Counter;
class User;
class UsersRepository
{
    public:
        UsersRepository();
        ~UsersRepository();
        void addUser(User* new_user);
        User* findUser(std::string username, std::string password);
        User* findPublisher(int publisher_id);
        User* findPeople(int user_id);
        int getUsersNumber();
        std::vector<User*> copyUsers(std::vector<User*> temp);
    private:
        std::vector<User*> users;
        int last_id;
};
#endif