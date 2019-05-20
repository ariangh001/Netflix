#include "System.h"

System::System()
{
    users_repo = new UsersRepository();
    movie_repo = new MovieRepository();
    comment_repo = new CommentRepository();
    process_handler = new ProcessHandler(users_repo,movie_repo,comment_repo);
    input_handler = new InputHandler(process_handler);
}