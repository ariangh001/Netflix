#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include "ExceptionHandler.h"
#include "Comment.h"
#include "Reply.h"
class Movie
{
    public:
        Movie(std::string _name, int _year,
            int _length, int _price, std::string _summary,
             std::string _director, int _rate, int _publisher_id);
        ~Movie();
        void addRate(int user_id, int _rate);
        void setId(int id);
        void setName(std::string _name);
        void setYear(int _year);
        void setPrice(int _price);
        void setLength(int _length);
        void setSummary(std::string _summary);
        void setDirector(std::string _director);
        std::string getName() const;
        int getYear() const;
        int getLength() const;
        int getPrice() const;
        int getPubId() const;
        std::string getSummary() const;
        std::string getDirector() const;
        int getId() const;
        float getRate() const;
        int getSold() const;
        void increaseSoldNumbers();
        void updateRate();
        void addComment(Comment* comment);
        void addReply(Reply* reply);
        void deleteComment(int comment_id);
        Comment* findComment(int comment_id);
        void showCommentsDetails();
        bool isDeleted();
        void deleteMovie();
    private:
        std::string name;
        int year;
        int length;
        int price;
        std::string summary;
        std::string director;
        int id;
        int publisher_id;
        float rate;
        int numbers_sold;
        std::map<int,int> rates;
        std::vector<Comment*> comments;
        std::vector<Reply*> replies;
        int last_comment_id;
        bool is_deleted;
};

#endif