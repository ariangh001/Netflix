#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>
class Movie
{
    public:
        Movie(std::string _name, int _year,
            int _length, int _price,
            std::string _summary, std::string _director,int _rate);
        void setId(int id);
        void setId(int _id);
        void setName(std::string _name);
        void setYear(int _year);
        void setPrice(int _price);
        void setLength(int _length);
        void setSummary(std::string _summary);
        void setDirector(std::string _director);
        // std::string getName() const;
        // int getYear() const;
        // int getLength() const;
        // int getPrice() const;
        // std::string getSummary() const;
        // std::string getDirector() const;
        int getId() const;
        // int getRate() const;
    private:
        std::string name;
        int year;
        int length;
        int price;
        std::string summary;
        std::string director;
        int id;
        std::vector<int> rates;
        float rate;
        int numbers_sold;
};

#endif