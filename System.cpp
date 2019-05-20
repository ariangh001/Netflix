#include "System.h"

System::System()
{
    process_handler = new ProcessHandler(users_repo,movie_repo,comment_repo);
    input_handler = new InputHandler(process_handler);
}