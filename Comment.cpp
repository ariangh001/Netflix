#include "Comment.h"

Comment::Comment(std::string _content, int _user_id, int _movie_id)
{
    id = 0;
    content = _content;
    user_id = _user_id;
    movie_id = _movie_id;
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