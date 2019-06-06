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

Response* SignUpHandler::callback(Request* req)
{
    try
    {
        Map signUpInput = {{"email",""},{"username",""},
            {"password",""},{"age",""},{"is_publisher",""}};
        signUpInput["username"] = req->getBodyParam("username");
        signUpInput["password"] = req->getBodyParam("password");
        signUpInput["email"] = req->getBodyParam("email");
        signUpInput["age"] = req->getBodyParam("age");
        signUpInput["is_publisher"] = req->getBodyParam("is_publisher");
        handler->checkInput(signUpInput,"signup");
        std::string session_id = handler->signup(signUpInput,"signup");
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

Response* LogoutHandler::callback(Request* req)
{
    try
    {
        std::string req_session = req->getSessionId();
        handler->logout(req_session);
        Response* res = Response::redirect("/");
        res->setHeader("Content-Type","text/html");
        res->setHeader("Developer-Name","ariyan");
        res->setSessionId("");
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
