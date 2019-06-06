#include "System.h"

System::System()
{
    users_repo = new UsersRepository();
    movie_repo = new MovieRepository();
    process_handler = new ProcessHandler(users_repo,movie_repo);
    input_handler = new InputHandler(process_handler);
}

System::~System()
{
    delete users_repo;
    delete movie_repo;
    delete process_handler;
    delete input_handler;
}