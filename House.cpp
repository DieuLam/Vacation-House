#include "House.h"
#include "Rating.h"
#include "Request.h"
#include "Member.h"

House::House(){};

House::House(Member *owner, string city, string description,string startDate, string endDate, double minRating, int conCredits)
{
    this->owner = owner;
    this->city = city;
    this->description = description;
    this->startDate = startDate;
    this->endDate = endDate;
    this->consummingCredits = conCredits;
    this->minOccRating = minRating;
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
                 << i+1 << ". " << list.at(i)->username << "\n";
            cout << "- Full name: " << list.at(i)->fullName << "\n";
            cout << "- Contact number: " << list.at(i)->phone << "\n";
            cout << "- Rating: " << Rating::calculateScores(list.at(i)->ratings) << "\n";
            cout << "- Rent from " << list.at(i)->startDate << " to " << list.at(i)->endDate << "\n";
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

void House::addRequest(Member *member, string start, string end, int numDay)
{
    if (member != this->owner)
    {
        this->requestList.push_back(new Request(member, this, start, end, numDay));
    }
};
