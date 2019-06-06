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
        server.setNotFoundErrPage("static/NotFound.html");
        server.get("/", new ShowPage("static/root.html"));
        server.get("/signup", new ShowPage("static/Signup.html"));
        server.post("/signup", new SignUpHandler(process_handler));
        server.get("/logoe3.png", new ShowImage("image/logoe3.png"));
        server.get("/back.jpg", new ShowImage("image/back.jpg"));
        server.get("/Welcome_To_UTFLIX.png", new ShowImage("image/Welcome_To_UTFLIX.png"));
        server.get("/login", new ShowPage("static/Login.html"));
        server.post("/login", new LoginHandler(process_handler));
        server.get("/logout",new LogoutHandler(process_handler));
        server.get("/home", new Home(process_handler));
        server.get("/profile", new Profile(process_handler));
        server.get("/moviedetails", new MovieDetails(process_handler));
        server.post("/submitfilm", new SubmitFilm(process_handler));
        server.get("/submitfilm", new ShowPage("static/AddMovie.html"));
        server.get("/submitsuccess", new ShowPage("static/SubmitSuccess.html"));
        server.get("/permissionerror", new ShowPage("static/PermissionError.html"));
        server.get("/notfound", new ShowPage("static/NotFoundError.html"));
        server.get("/badrequest", new ShowPage("static/BadRequestError.html"));
        server.get("/new.jpg",new ShowImage("image/new.jpg"));
        server.get("/not_found.jpeg",new ShowImage("image/not_found.jpeg"));
        server.get("/68343621-permission-denied-rubber-stamp.jpg", new ShowImage("image/68343621-permission-denied-rubber-stamp.jpg"));
        server.get("/fail.png", new ShowImage("image/fail.png"));
        server.get("/University_of_Tehran_logo.svg.png", new ShowImage("image/University_of_Tehran_logo.svg.png"));
        server.run();
    }
    catch(Server::Exception &e)
    {
        std::cout << e.getMessage() << '\n';
    }
}