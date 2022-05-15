#include "Member.h"
#include "House.h"
#include "Rating.h"
#include "Request.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "DataHandler.h"
#include <math.h>

Member::Member(){};

Member::Member(string username, string password, string fullName, string phone)
{
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->phone = phone;
}

void Member::showMemberInfo()
{
    cout << "\nYour Profile:\n";
    cout << "- Username: " << this->username << "\n";
    cout << "- Password: " << this->username << "\n";
    cout << "- Fullname: " << this->fullName << "\n";
    cout << "- Phone number: " << this->phone << "\n";
    cout << "- Rating: " << Rating::calculateScores(this->ratings) << "\n";
    cout << "- Credits: " << this->credit << "\n";
    cout << "- House occupied: " << this->houseOccupied << "\n";
}

void Member::showHouseInfo()
{
    if (this->houseOwned != NULL)
    {
        cout << "\nYour House Profile:\n";
        cout << "- Location: " << this->houseOwned->city << "\n";
        cout << "- Description: " << this->houseOwned->description << "\n";
        cout << "- Rating: " << Rating::calculateScores(this->houseOwned->ratings) << "\n";
        cout << "- Number of requests: " << this->houseOwned->requestList.size() << "\n";
        cout << "- Consuming credits: " << this->houseOwned->consummingCredits << "\n";
        cout << "- Minimum Occupier Rating: " << this->houseOwned->minOccRating << "\n";
        cout << "- Occupied by " << this->houseOwned->occupierList.size() << " people\n";
        for (int i = 0; i < this->houseOwned->occupierList.size(); i++)
        {
            cout << i << ". " << this->houseOwned->occupierList.at(i) << "\n";
            cout << "Time: " << this->houseOwned->occupierList.at(i)->startDate << " to " << this->houseOwned->occupierList.at(i)->endDate << "\n";
        }
    }
    cerr << "\nYou have to add your house first\n";
};

Member *Member::login()
{
    string tempUsername;
    string tempPass;
    cout << "Please enter your username: ";
    getline(cin, tempUsername);
    cout << "Please enter your password: ";
    getline(cin, tempPass);

    for (Member *m : DataHandler::memberList)
    {
        if ((m->username).compare(tempUsername) == 0)
        {
            if ((m->password).compare(tempPass) == 0)
            {
                cout << "Login successfully!\n";
                return m;
            }
            else
            {
                cerr << "Incorrect password!\n";
                return NULL;
            }
        }
    }

    cerr << "Account does not exist\n";
    return NULL;
};

void Member::addHouse()
{
    if (this->houseOwned == NULL)
    {
        string location, description;
        cout << "\nPlease provide the location of your house: ";
        getline(cin, location);
        cout << "Please provide description for your house: ";
        getline(cin, description);
        this->houseOwned = new House(this, location, description);

        cout << "You have successfully added a house.\n";
    }
    else
    {
        cerr << "\nYou cannot have more than 1 house\n";
    }
};

bool Member::listHouse()
{
    if (this->houseOwned != NULL)
    {
        if (this->houseOwned->startDate == "")
        {
            string start, end;
            string rating, credit;

            cout << "\nPlease set the availability of your house \n";
            cout << "Start date (yyyy/mm/dd): ";
            getline(cin, start);
            cout << "End date (yyyy/mm/dd): ";
            getline(cin, end);
            cout << "Consunming points per day: ";
            getline(cin, credit);
            cout << "Minimum required occupier rating (0 -> 10): ";
            getline(cin, rating);
            this->houseOwned->setData(start, end, stod(rating), stod(credit));

            cout << "You have successfully listed your house.\n";
            return true;
        }
        else
        {
            cerr << "You have already listed your house. You can only unlist it.\n";
            return false;
        }
    }
    else
    {
        cerr << "You need to add your house first\n";
        return false;
    }
};

bool Member::unlistHouse()
{
    if (this->houseOwned != NULL)
    {
        if (this->houseOwned->startDate != "")
        {
            this->houseOwned->setData("", "", 0.0, 0.0);

            cout << "You have successfully unlisted your house.\n";
            return true;
        }
        else
        {
            cerr << "You have already unlisted your house. You can only list it.\n";
            return false;
        }
    }
    else
    {
        cerr << "You need to add your house first\n";
        return false;
    }
};

void Member::sendRequest(int num)
{
    if (this->houseOccupied == NULL)
    {
        this->availableHouses.at(num)->addRequest(this, this->startDate, this->endDate);
        this->requestSentList.push_back(new Request(this, this->availableHouses.at(num), this->startDate, this->endDate));
        cout << "Your request has successlly sent\n";
    }
    else
    {
        cerr << "You cannot occupy more than 1 house\n";
    }
};

bool Member::viewRequest()
{
    if (this->houseOwned == NULL)
    {
        cerr << "\nYou have to add your house first\n";
        return false;
    }

    vector<Request *> list = this->houseOwned->requestList;

    if (list.size() == 0)
    {
        cout << "\nNo occupying requests for this house\n";
        return false;
    }

    cout << "\nThere are " << list.size() << " people request to rent this house: \n\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << i << ". " << list.at(i)->sender->username << "\n";
        cout << "- Full name: " << list.at(i)->sender->fullName << "\n";
        cout << "- Contact number: " << list.at(i)->sender->phone << "\n";
        cout << "- Rating: " << Rating::calculateScores(list.at(i)->sender->ratings) << "\n";
        cout << "- Request to rent from " << list.at(i)->startDate << " to " << list.at(i)->endDate << "\n";
    }
    return true;
};

bool Member::acceptRequest(int num)
{
    if (this->houseOwned == NULL)
    {
        return false;
    }
    vector<Request *> list = this->houseOwned->requestList;
    if (!list.empty())
    {
        this->houseOwned->addOccupier(list.at(num)->sender);
        this->houseOwned->resetDate(list.at(num)->startDate);
        list.at(num)->sender->houseOccupied = this->houseOwned;
        list.at(num)->sender->requestSentList.clear();

        // Check requestList of house to delete overlapped time request
        for (Request *r : list)
        {
            if ((r->startDate >= list.at(num)->startDate) && (r->startDate <= list.at(num)->endDate) || (r->endDate >= list.at(num)->startDate) && (r->endDate <= list.at(num)->endDate))
            {
                remove(list.begin(), list.end(), r);
            }
        }

        list.at(num)->sender->startDate = list.at(num)->startDate;
        list.at(num)->sender->endDate = list.at(num)->endDate;

        cout << "You have accepted this request\n";
        return true;
    }

    return false;
};

void Member::cancelRequest(){

};

// ----------------------------------------NU------------------------------------- //

template <class T>
void Member::rate(T *object)
{
    if (object != NULL)
    {

        double score;
        string comment;
        cout << "How many scores would you like to give (0 -> 10)? \n";
        cin >> score;
        cout << "Would you like to leave a comment? (Y/N) \n";
        getline(cin, comment);
        if (comment.compare("Y") == 0)
        {
            cout << "Please write your comment down here: \n\n";
            getline(cin, comment);
        }
        else
        {
            comment = "";
        }
        cout << "Thank you! \n";
        object->ratings.push_back(new Rating(this, comment, score));
    }
};

template void Member::rate(Member *);
template void Member::rate(House *);

void Member::rateMember()
{
    if (this->houseOwned == NULL)
    {
        cerr << "/nYou need to add your house first/n";
    }
    else if (!this->houseOwned->occupierList.empty())
    {
        string option;
        this->houseOwned->showOccupierList();
        cout << "\nPlease choose a occupier by entering a number: \n";
        getline(cin, option);
        this->rate<Member>(this->houseOwned->occupierList.at(stoi(option) - 1));
    }
    else
    {
        cerr << "\nYour house has not been rented by anyone\n";
    }
};

void Member::rateHouse()
{
    if (this->houseOccupied != NULL)
    {
        this->rate<House>(this->houseOccupied);
    }
    else
    {
        cerr << "\nYou have not occupied any house\n";
    }
};

//--------------------------- calc day between ----------------------------------------//

const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243,
                           273, 304, 334, 365};
int countLeapYearDays(int d[])
{
    int years = d[2];
    if (d[1] <= 2)
        years--;
    return ((years / 4) - (years / 100) + (years / 400));
}
int countNoOfDays(int date1[], int date2[])
{
    long int dayCount1 = (date1[2] * 365);
    dayCount1 += monthDays[date1[1]];
    dayCount1 += date1[0];
    dayCount1 += countLeapYearDays(date1);
    long int dayCount2 = (date2[2] * 365);
    dayCount2 += monthDays[date2[1]];
    dayCount2 += date2[0];
    dayCount2 += countLeapYearDays(date2);
    return (abs(dayCount1 - dayCount2));
}
//-----------------------------------------------------------------------------------//

// reverse input
//  void reverseStr(string& str){
//      int n = str.length();
//     // Swap character starting from two
//     // corners
//     for (int i = 0; i < n / 2; i++)
//         std::swap(str[i], str[n - i - 1]);
// }

bool Member::checkAvailableHouses()
{
    // member date select
    string startDate;
    string endDate;
    char fill = '/';
    int m_sMonth, m_sYear, m_sDay;
    int m_eMonth, m_eYear, m_eDay;
    string city;

    cout << "\nPlease provide the below information to search for available houses \n";
    // user input city
    cout << "City: ";
    getline(cin, city);
    // user input start day
    cout << "Start date (yyyy/mm/dd): ";
    getline(cin, startDate);
    // user input end day
    cout << "End date (yyyy/mm/dd): ";
    getline(cin, endDate);

    // get day, month, year
    m_sYear = stoi(startDate.substr(0, 4));
    m_sMonth = stoi(startDate.substr(5, 2));
    m_sDay = stoi(startDate.substr(8, 2));

    m_eYear = stoi(endDate.substr(0, 4));
    m_eMonth = stoi(endDate.substr(5, 2));
    m_eDay = stoi(endDate.substr(8, 2));

    int date1[3] = {m_sDay, m_sMonth, m_sYear};
    int date2[3] = {m_eDay, m_eMonth, m_eYear};
    int days = countNoOfDays(date1, date2);

    double score = Rating::calculateScores(this->ratings);
    for (Member *m : DataHandler::memberList)
    {
        if (m == this)
        {
            continue;
        }
        string HouseStart = m->houseOwned->startDate;
        string HouseEnd = m->houseOwned->endDate;

        if (m->houseOwned != NULL)
        {
            if (endDate < startDate)
            {
                cout << "\ninvalid\n";
            }
            else
            {
                if (city == m->houseOwned->city)
                {
                    if ((HouseStart <= startDate && startDate <= HouseEnd) && (HouseStart <= endDate && endDate <= HouseEnd))
                    {
                        if (m->houseOwned->consummingCredits * days <= m->credit)
                        {
                            if (score >= m->houseOwned->minOccRating)
                            {
                                this->availableHouses.push_back(m->houseOwned);
                            }
                            // else
                            // {
                            //     cout << "There are no house available!(rating)\n";
                            // }
                        }
                        // else {
                        //     cout << "Not enough credit!\n";
                        // }
                    }
                    // else
                    // {
                    //     cout << "There are no house available!(day)\n";
                    // }
                }
                // else
                // {
                //     cout << "There are no house available!(city)\n";
                // }
            }
        }
    }

    if (!this->availableHouses.empty())
    {
        cout << "\nThere are " << this->availableHouses.size() << " houses avaible to rent: \n";
        this->startDate = startDate;
        this->endDate = endDate;
        for (House *h : this->availableHouses)
        {
            cout << "\nOwner: " << h->owner->username << "\n";
            cout << "Rating: " << Rating::calculateScores(h->ratings) << "\n";
            cout << "Credit required per day: " << h->consummingCredits << "\n";
            cout << "Description: " << h->description << "\n";
        }
        return true;
    }
    else
    {
        cerr << "\nNo available houses.\n";
        return false;
    }
};

// Display review of selected house in the availableHouses attribute
void Member::viewReviews(int num)
{
    vector<Rating *> list = this->availableHouses.at(num)->ratings;
    if (list.size() > 0)
    {
        cout << "\nThere are " << list.size() << " reviews about this house\n";
        for (int i = 0; i < this->availableHouses.at(num)->ratings.size(); i++)
        {
            cout << "\n"
                 << i << ". " << list.at(i)->rater << "\n";
            cout << "Score: " << list.at(i)->score << "\n";
            cout << "Comment: " << list.at(i)->comment << "\n";
        }
    }
    else
    {
        cerr << "\nThere are no reviews\n";
    }
};

void Member::viewMemberReviews(int num)
{
    vector<Rating *> list = this->houseOwned->requestList.at(num)->sender->ratings;
    if (list.size() > 0)
    {
        cout << "\nThere are " << list.size() << " reviews about this Member\n";
        for (int i = 0; i < list.size(); i++)
        {
            cout << "\n"
                 << i << ". " << list.at(i)->rater << "\n";
            cout << "Score: " << list.at(i)->score << "\n";
            cout << "Comment: " << list.at(i)->comment << "\n";
        }
    }
    else
    {
        cerr << "There are no reviews\n";
    }
};

// int main()
// {
//     Member M1("trang", "111", "minhtrang", "123"); //"2022/04/20", "2022/6/25"
//     DataHandler::memberList.push_back(&M1);
//     Member M2("Thuan", "123", "Viet", "111"); //"2022/05/05", "2022/07/02"
//     DataHandler::memberList.push_back(&M2);
//     Member M3("Dieu", "Dieu", "Dieu", "222"); //"2022/06/10, 2022/08/15"
//     DataHandler::memberList.push_back(&M3);
//     Member M4("Cus", "Cus", "Cus", "012");
//     DataHandler::memberList.push_back(&M4);
//     M1.rate(&M4); // 6
//     M2.rate(&M4); // 5
//     M3.rate(&M4); // 8
//     House H1(&M1, "SG", "bla");
//     M1.houseOwned = &H1;
//     M1.listHouse(); // cre: 2, score: 4
//     House H2(&M2, "Hue", "cmt");
//     M2.houseOwned = &H2;
//     M2.listHouse(); // cre: 2, score: 3
//     House H3(&M3, "SG", "cm12");
//     M3.houseOwned = &H3;
//     M3.listHouse(); // cre: 2, score: 7
//     M4.checkAvailableHouses(&M4);
//     return 0;
// }
