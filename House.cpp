#include "header_files/House.h"
#include "header_files/Rating.h"
#include "header_files/Request.h"
#include "header_files/Member.h"

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

// display all occupiers of the house
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

// display basic house info for non-member
void House::showInfo()
{
    cout << "Location: " << this->city << "\n";
    cout << "Description: " << this->description << "\n";
};

// set data of the house when member list the house
void House::setData(string startDate, string endDate, double minRating, double conCredits)
{
    this->startDate = startDate;
    this->endDate = endDate;
    this->minOccRating = minRating;
    this->consummingCredits = conCredits;
};

// add a member to the occupier list of the house
void House::addOccupier(Member *member)
{
    if (member != this->owner)
    {
        for (Member *m : this->occupierList) {
            if (m == member) {
                return;
            }
        }
        this->occupierList.push_back(member);
    }
};

// add a request to the request list
void House::addRequest(Member *member, string start, string end, int numDay)
{
    if (member != this->owner)
    {
        this->requestList.push_back(new Request(member, this, start, end, numDay));
    }
};
