#ifndef USERS_REPOSITORY_H
#define USERS_REPOSITORY_H
#include "User.h"
#include <vector>
class UsersRepository
{
    public:
        void addUser(User* new_user);
        

    private:
        std::vector<User*> users;
};
#endif