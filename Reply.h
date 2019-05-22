#ifndef REPLY_H
#define REPLY_H
#include <string>
class Reply
{
    public:
        Reply(int comment_id, int _pub_id,
                 int _movie_id , std::string _content);
    private:
        int id;
        int publisher_id;
        int movie_id;
        std::string content;
};
#endif