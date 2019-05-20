#include "UsersRepository.h"

UsersRepository::UsersRepository()
{
    last_id = 0;
}

void UsersRepository::addUser(User* user)
{
    last_id++;
    user->setId(last_id);
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

User* UsersRepository::findPublisher(int publisher_id)
{
    if(publisher_id <= 0)
        throw BadRequest();
    for(Counter i=0; i<users.size(); i++)
        if(users[i]->getId() == publisher_id)
            return users[i];
    throw NotFound();
}