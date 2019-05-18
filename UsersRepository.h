#ifndef USERS_REPOSITORY_H
#define USERS_REPOSITORY_H
#include "User.h"
#include <vector>
class UsersRepository
{
    public:
        void addUser(User* new_user);
        User* findUser(std::string username, std::string password);
    private:
        std::vector<User*> users;
};
#endif