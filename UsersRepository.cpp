#include "UsersRepository.h"

void UsersRepository::addUser(User* user)
{
    users.push_back(user);
}

User* UsersRepository::findUser(std::string username, std::string password)
{
    for(Counter i=0; i<users.size(); i++)
    {
        if(users[i]->getUsername() == username)
        {
            if(users[i]->getPassword() == password)
                return users[i];
            else
                throw BadRequest();
        }
    }
    throw BadRequest();
}

int UsersRepository::getUsersNumber()
{
    return users.size();
}