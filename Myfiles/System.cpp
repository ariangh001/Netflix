#include "System.h"

System::System(int argc,char** argv)
{
    users_repo = new UsersRepository();
    movie_repo = new MovieRepository();
    process_handler = new ProcessHandler(users_repo,movie_repo);
    run(argc,argv);
}

System::~System()
{
    delete users_repo;
    delete movie_repo;
    delete process_handler;
}