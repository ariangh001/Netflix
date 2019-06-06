#ifndef SYSTEM_H
#define SYSTEM_H
#include "UsersRepository.h"
#include "MovieRepository.h"
#include "InputHandler.h"
#include "ProcessHandler.h"
#include "my_server.hpp"
#include "RequestHandlers.h"
class System
{
    public:
        System(int argc,char** argv);
        ~System();
        void run(int argc,char** argv);
    private:
        UsersRepository* users_repo;
        MovieRepository* movie_repo;
        InputHandler* input_handler;
        ProcessHandler* process_handler;
};
#endif