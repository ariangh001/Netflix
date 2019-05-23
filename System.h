#ifndef SYSTEM_H
#define SYSTEM_H
#include "UsersRepository.h"
#include "MovieRepository.h"
#include "InputHandler.h"
#include "ProcessHandler.h"
class System
{
    public:
        System();
    private:
        UsersRepository* users_repo;
        MovieRepository* movie_repo;
        InputHandler* input_handler;
        ProcessHandler* process_handler;
};
#endif