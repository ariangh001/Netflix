#include "RequestHandlers.h"

LoginHandler::LoginHandler(ProcessHandler* _handler)
{
    handler = _handler;
}

SignUpHandler::SignUpHandler(ProcessHandler* _handler)
{
    handler = _handler;
}

LogoutHandler::LogoutHandler(ProcessHandler* _handler)
{
    handler = _handler;
}

SubmitFilm::SubmitFilm(ProcessHandler* _handler)
{
    handler = _handler;
}

Profile::Profile(ProcessHandler* _handler)
{
    handler = _handler;
}

Home::Home(ProcessHandler* _handler)
{
    handler = _handler;
}

MovieDetails::MovieDetails(ProcessHandler* _handler)
{
    handler = _handler;
}

Response* LoginHandler::callback(Request* req)
{
    try
    {
        Map loginInput = {{"username",""},{"password",""}};
        loginInput["username"] = req->getBodyParam("username");
        loginInput["password"] = req->getBodyParam("password");
        handler->checkInput(loginInput,"login");
        std::string session_id = handler->login(loginInput,"login");
        Response* res = Response::redirect("/home");
        res->setHeader("Content-Type","text/html");
        res->setHeader("Developer-Name","ariyan");
        res->setSessionId(session_id);
        return res;
    }
    catch(std::exception& e)
    {
        std::string exc = e.what();
        if(exc == "Bad Request")
        {
            Response* failed = Response::redirect("/badrequest");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Permission Denied")
        {
            Response* failed = Response::redirect("/permissionerror");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
        if(exc == "Not Found")
        {
            Response* failed = Response::redirect("/notfound");
            failed->setHeader("Content-Type","text/html");
            failed->setHeader("Developer-Name","ariyan");
            return failed;
        }
    }
}
