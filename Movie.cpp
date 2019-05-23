#include "MovieRepository.h"

Movie::Movie(std::string _name, int _year,int _length, int _price,
            std::string _summary, std::string _director, int _rate, int _publisher_id)
{
    name = _name;
    publisher_id = _publisher_id;
    year = _year;
    length = _length;
    price = _price;
    summary = addSpaces(_summary);
    director = _director;
    rate = _rate;
    numbers_sold = 0;
    last_comment_id = 0;
}

std::string Movie::addSpaces(std::string _string)
{
    for(Counter i=0; i<_string.size(); i++)
        if(_string[i] == '|')
            _string[i] = ' ';
    return _string;
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

float Movie::getRate() const
{
    return rate;
}

int Movie::getPubId() const
{
    return publisher_id;
}

void Movie::setId(int _id)
{
    if(_id > 0)
        id = _id;
    else
        throw BadRequest();
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
    else
        throw BadRequest();
}

void Movie::setPrice(int _price)
{
    if(_price >= 0)
        price = _price;
    else
        throw BadRequest();
}

void Movie::setLength(int _length)
{
    if(_length > 0)
        length = _length;
    else
        throw BadRequest();
}

void Movie::setSummary(std::string _summary)
{
    summary = _summary;
}

void Movie::addRate(int user_id, int _rate)
{
    auto itr = rates.find(user_id);
    if(_rate >= 0 && _rate <= 10)
        rates[user_id] = _rate;
    else
        throw BadRequest();
}

void Movie::increaseSoldNumber()
{
    numbers_sold++;
}

int Movie::getSold() const
{
    return numbers_sold;
}

int Movie::getRecievedCash() const
{
    return cash_recieved_number;
}

int Movie::setRecievedCash(int amount)
{
    if(amount >= 0)
        cash_recieved_number = amount;
}

void Movie::updateRate()
{
    float sum = 0;
    for(auto itr = rates.begin(); itr!=rates.end(); itr++)
        sum += itr->second;
    rate = sum / rates.size();
}

void Movie::addComment(Comment* comment)
{
    last_comment_id++;
    comment->setId(last_comment_id);
    comments.push_back(comment);
}

void Movie::addReply(Reply* reply)
{
    replies.push_back(reply);
}

Comment* Movie::findComment(int comment_id)
{
    if(comment_id <= 0)
        throw BadRequest();
    for(Counter i=0; i<comments.size(); i++)
        if(comments[i]->getId() == comment_id)
            return comments[i];
    throw NotFound();
}

void Movie::deleteComment(int comment_id)
{
    if(comment_id <= 0)
        throw BadRequest();
    for(Counter i=0; i<comments.size(); i++)
        if(comments[i]->getId() == comment_id)
        {
            comments.erase(comments.begin() + i);
            return;
        }
    throw NotFound();
}