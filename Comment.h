#ifndef COMMENT_H
#define COMMENT_H
#include <string>
class Comment
{
    public:
        Comment(int _id, std::string _content);
        // int getId() const;
        // std::string getContent() const;
    private:
        int id;
        std::string content;
};
#endif