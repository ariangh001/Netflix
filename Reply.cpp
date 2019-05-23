#include "Reply.h"

Reply::Reply(int comment_id, int _pub_id,
                 int _movie_id , std::string _content)
{
    if(comment_id > 0 && _pub_id > 0 && _movie_id > 0)
    {
        id = comment_id;
        publisher_id = _pub_id;
        movie_id = _movie_id;
    }
    else
        throw BadRequest();
    content = _content;
}

int Reply::getId() const
{
    return id;
}

std::string Reply::getContent() const
{
    return content;
}