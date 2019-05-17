#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H
#include <exception>
#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"
#define OK_REQUEST "OK"
class NotFound : public std::exception
{
    public:
        virtual const char* what() const throw();
};

class BadRequest : public std::exception
{
    public:
        virtual const char* what() const throw();
};

class PermissionDenied : public std::exception
{
    public:
        virtual const char* what() const throw();
};

#endif