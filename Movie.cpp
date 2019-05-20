#include "MovieRepository.h"

Movie::Movie(std::string _name, int _year,int _length, int _price,
            std::string _summary, std::string _director, int _rate)
{
    name = _name;
    year = _year;
    length = _length;
    price = _price;
    summary = _summary;
    director = _director;
    rate = _rate;
    numbers_sold = 0;
}

void Movie::setId(int _id)
{
    if(_id > 0)
        id = _id;
}

void Movie::setDirector(std::string _director)
{
    director = _director;
}

void Movie::setName(std::string _name)
{
    name = _name;
}

void Movie::setYear(int _year)
{
    if(_year > 0)
        year = _year;
}

void Movie::setPrice(int _price)
{
    if(_price >= 0)
        price = _price;
}

void Movie::setLength(int _length)
{
    if(_length > 0)
        length = _length;
}

void Movie::setSummary(std::string _summary)
{
    summary = _summary;
}