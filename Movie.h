#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>
#include <map>
#include <iterator>
class Movie
{
    public:
        Movie(std::string _name, int _year,
            int _length, int _price,
            std::string _summary, std::string _director,int _rate);
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
        std::string getSummary() const;
        std::string getDirector() const;
        int getId() const;
        float getRate() const;
        int getSold() const;
        void increaseSoldNumber();
        void updateRate();
        std::string addSpaces(std::string _string);
        int getRecievedCash() const;
        int setRecievedCash(int amount);
    private:
        std::string name;
        int year;
        int length;
        int price;
        std::string summary;
        std::string director;
        int id;
        float rate;
        int numbers_sold;
        int cash_recieved_number;
        std::map<int,int> rates;
};

#endif