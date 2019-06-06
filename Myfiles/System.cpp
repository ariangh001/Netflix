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

void System::run(int argc,char** argv)
{
    try
    {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        //server.setNotFoundErrPage("static/NotFound.html");
        server.get("/", new ShowPage("static/root.html"));
        server.get("/signup", new ShowPage("static/Signup.html"));
        server.post("/signup", new SignUpHandler(process_handler));
        server.get("/logoe3.png", new ShowImage("image/logoe3.png"));
        server.get("/back.jpg", new ShowImage("image/back.jpg"));
        server.get("/Welcome_To_UTFLIX.png", new ShowImage("image/Welcome_To_UTFLIX.png"));
        server.get("/login", new ShowPage("static/Login.html"));
        server.post("/login", new LoginHandler(process_handler));
        server.get("/logout",new LogoutHandler(process_handler));
    }
    catch(Server::Exception &e)
    {
        std::cout << e.getMessage() << '\n';
    }
}