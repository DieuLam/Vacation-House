#include "Member.h"
#include "House.h"
#include "Rating.h"
#include "Request.h"

House::House(){};

House::House(Member *owner, string city, string description)
{
    this->owner = owner;
    this->city = city;
    this->description = description;
};

void House::setData(string startDate, string endDate, int minRating, double conCredits)
{
    this->startDate = startDate;
    this->endDate = endDate;
    this->minOccRating = minRating;
    this->consummingCredits = conCredits;
};

void House::resetDate(string date)
{
    this->startDate = date;
};

void House::addOccupier(Member *member)
{
    if (member != this->owner)
    {
        this->occupierList.push_back(member);
    }
};

void House::addRequest(Member *member, string start, string end)
{
    if (member != this->owner)
    {
        this->requestList.push_back(new Request(member, this, start, end));
    }
};