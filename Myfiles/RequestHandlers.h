#ifndef REQUEST_HANDLERS_H
#define REQUEST_HANDLERS_H
#include "../server/server.hpp"
#include "ExceptionHandler.h"
#include "ProcessHandler.h"
#include <map>
#include <iterator>
typedef std::map<std::string,std::string> Map;
class LoginHandler : public RequestHandler
{
    public:
        LoginHandler(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

class SignUpHandler : public RequestHandler
{
    public:
        SignUpHandler(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

class LogoutHandler : public RequestHandler
{
    public:
        LogoutHandler(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

class SubmitFilm : public RequestHandler
{
    public:
        SubmitFilm(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

class Profile : public RequestHandler
{
    public:
        Profile(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

class Home : public RequestHandler
{
    public:
        Home(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

class MovieDetails : public RequestHandler
{
    public:
        MovieDetails(ProcessHandler* _handler);
        Response *callback(Request *);
    private:
        ProcessHandler* handler;
};

#endif