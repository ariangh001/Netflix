#include "MovieRepository.h"

Movie::Movie(std::string _name, int _year,int _length, int _price,
            std::string _summary, std::string _director, int _rate, int _publisher_id)
{
    if(_year > 0 && _length > 0 && _price > 0 && _rate >= 0 && _rate <= 10 && _publisher_id > 0)
    {
        publisher_id = _publisher_id;
        year = _year;
        length = _length;
        price = _price;
        rate = _rate;
    }
    else
        throw BadRequest();
    name = _name;
    summary = _summary;
    director = _director;
    last_comment_id = 0;
    id = 0;
    numbers_sold = 0;
    is_deleted = false;
}

Movie::~Movie()
{
    for(Counter i=0; i<comments.size(); i++)
        delete comments[i];
    for(Counter i=0; i<replies.size(); i++)
        delete replies[i];
}

bool Movie::isDeleted()
{
    return is_deleted;
}

void Movie::deleteMovie()
{
    is_deleted = true;
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

int Movie::getSold() const
{
    return numbers_sold;
}

void Movie::increaseSoldNumbers()
{
    numbers_sold++;
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
    {
        if(itr != rates.end())
            itr->second = _rate;
        else
            rates.insert({user_id , _rate});
    }
    else
        throw BadRequest();
}

void Movie::updateRate()
{
    float sum = 0;
    for(auto itr = rates.begin(); itr!=rates.end(); itr++)
        sum+= itr->second;
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

void Movie::showCommentsDetails()
{
    for(Counter i=0; i<comments.size(); i++)
    {
        std::cout<<comments[i]->getId()<<". "<<comments[i]->getContent()<<std::endl;
        for(Counter j=0; j<replies.size(); j++)
            if(replies[j]->getId() == comments[i]->getId())
                std::cout<<comments[i]->getId()<<'.'
                         <<j+1<<". "<<replies[j]->getContent()<<std::endl;
    }
}