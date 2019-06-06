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
