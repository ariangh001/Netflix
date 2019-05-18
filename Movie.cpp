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
    id = _id;
}