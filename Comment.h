#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include "ExceptionHandler.h"
class Comment
{
    public:
        Comment(std::string _content, int _user_id, int _movie_id);
        void setId(int _id);
        int getId() const;
        std::string getContent() const;
    private:
        int user_id;
        int movie_id;
        int id;
        std::string content;
};
#endif