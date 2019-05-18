#ifndef MOVIE_H
#define MOVIE_H
#include <string>
class Movie
{
    public:
        Movie(std::string _name, int _year,
            int _length, int _price,
            std::string _summary, std::string _director,
            int _id, int _rate);
        void setId(int id);
        // std::string getName() const;
        // int getYear() const;
        // int getLength() const;
        // int getPrice() const;
        // std::string getSummary() const;
        // std::string getDirector() const;
        // int getId() const;
        // int getRate() const;
    private:
        std::string name;
        int year;
        int length;
        int price;
        std::string summary;
        std::string director;
        int id;
        int rate;
};

#endif