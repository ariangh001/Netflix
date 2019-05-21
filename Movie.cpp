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

int Movie::getId() const
{
    return id;
}

std::string Movie::getName() const
{
    return name;
}

int Movie::getYear() const
{
    return year;
}

int Movie::getLength() const
{
    return length;
}

int Movie::getPrice() const
{
    return price;
}

std::string Movie::getSummary() const
{
    return summary;
}

std::string Movie::getDirector() const
{
    return director;
}

int Movie::getRate() const
{
    return rate;
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

void Movie::addRate(int user_id, int _rate)
{
    auto itr = rates.find(user_id);
    if(_rate >= 0)
        rates[user_id] = _rate;
    else
        throw BadRequest();
}