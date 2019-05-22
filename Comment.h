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
        int getMovieId() const;
        std::string getContent() const;
    private:
        std::string content;
        int user_id;
        int movie_id;
        int id;
};
#endif