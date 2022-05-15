//#include "Member.h"
#include "House.h"
#include "Rating.h"
#include "Request.h"
#include "Member.h"

House::House(){};

House::House(Member *owner, string city, string description)
{
    this->owner = owner;
    this->city = city;
    this->description = description;
};

void House::showOccupierList()
{
    vector<Member *> list = this->occupierList;

    if (!list.empty())
    {
        cout << "\nThere are " << list.size() << " people rent your house: \n";
        for (int i = 0; i < list.size(); i++)
        {
            cout << "\n"
                 << i << ". " << list.at(i)->username << "\n";
            cout << "- Full name: " << list.at(i)->fullName << "\n";
            cout << "- Contact number: " << list.at(i)->phone << "\n";
            cout << "- Rating: " << Rating::calculateScores(list.at(i)->ratings) << "\n";
            cout << "- Rent from " << list.at(i)->requestSentList.at(0)->startDate << " to " << list.at(i)->requestSentList.at(0)->endDate << "\n";
        }
    }
    else
    {
        cerr << "\nYou house has not been rent by anyone yet \n";
    }
};

void House::showInfo()
{
    cout << "Location: " << this->city << "\n";
    cout << "Description: " << this->description << "\n";
};

void House::setData(string startDate, string endDate, double minRating, double conCredits)
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