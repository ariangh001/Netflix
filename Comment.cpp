#include "Comment.h"

Comment::Comment(std::string _content, int _user_id, int _movie_id)
{
    id = 0;
    content = _content;
    if(_user_id > 0 && _movie_id > 0)
    {
        user_id = _user_id;
        movie_id = _movie_id;
    }
    else
        throw BadRequest();
}

void Comment::setId(int _id)
{
    if(_id > 0)
        id = _id;
    else
        throw BadRequest();
}

int Comment::getId() const
{
    return id;
}

std::string Comment::getContent() const
{
    return content;
}

int Comment::getMovieId() const
{
    return movie_id;
}
int Comment::getUserId() const
{
    return user_id;
}