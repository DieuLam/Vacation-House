#include "header_files/Member.h"
#include "header_files/House.h"
#include "header_files/Rating.h"
#include "header_files/Request.h"
#include "header_files/DataHandler.h"
#include "checkInput.cpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>

Member::Member(){};

Member::Member(string username, string password, string fullName, string phone, int credit)
{
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->phone = phone;
    this->credit = credit;
}

void Member::showMemberInfo()
{
    cout << "\nProfile:\n";
    cout << "- Username: " << this->username << "\n";
    cout << "- Fullname: " << this->fullName << "\n";
    cout << "- Phone number: " << this->phone << "\n";
    cout << "- Rating: " << Rating::calculateScores(this->ratings) << "\n";
    cout << "- Credits: " << this->credit << "\n";
    if (houseOccupied != NULL)
    {

        cout << "- House occupied: " << this->houseOccupied->owner->username << "\n";
    }
    else
    {
        cout << "- House occupied: None \n";
    }
}

void Member::showHouseInfo()
{
    if (this->houseOwned != NULL)
    {
        cout << "\nHouse Profile:\n";
        cout << "- Location: " << this->houseOwned->city << "\n";
        cout << "- Description: " << this->houseOwned->description << "\n";
        cout << "- Rating: " << Rating::calculateScores(this->houseOwned->ratings) << "\n";
        cout << "- Number of requests: " << this->houseOwned->requestList.size() << "\n";
        cout << "- Consuming credits: " << this->houseOwned->consummingCredits << "\n";
        cout << "- Minimum Occupier Rating: " << this->houseOwned->minOccRating << "\n";
        cout << "- Available to rent from " << this->houseOwned->startDate << " to " << this->houseOwned->endDate << "\n";
        cout << "- Occupied by " << this->houseOwned->occupierList.size() << " people\n";
        for (int i = 0; i < this->houseOwned->occupierList.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". " << this->houseOwned->occupierList.at(i)->username << "\n";
            cout << "Time: " << this->houseOwned->occupierList.at(i)->startDate << " to " << this->houseOwned->occupierList.at(i)->endDate << "\n";
        }
    }
    else
    {
        cerr << "\nYou need to add your house first\n";
    }
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
                cout << "\nLogin successfully!\n";
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
        bool validInput = false;
        string location, description;
        cout << "\nPlease provide information of your house: \n";

        while (validInput != true)
        {
            // user input city
            cout << "Location (Saigon/Hanoi/Da Nang): ";
            getline(cin, location);
            validInput = checkCity(location);
        }

        cout << "Description: ";
        getline(cin, description);
        this->houseOwned = new House(this, location, description, "", "", 0, 0);

        DataHandler::addHouse(houseOwned);

        cout << "\nYou have successfully added a house.\n";
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
            string start, end, h_sDay, h_sMonth, h_sYear, h_eDay, h_eMonth, h_eYear;
            string rating, credit;

            bool validInput = false;
            while (validInput != true)
            {
                // user input start day
                cout << "\nEnter your house start date\n";
                cout << "Day (dd): ";
                getline(cin, h_sDay);
                validInput = checknum(h_sDay);
                ;
                if (validInput == 0) // means validInput = false
                    continue;
            }

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                // user input start day
                cout << "Month (mm): ";
                getline(cin, h_sMonth);
                validInput = checknum(h_sMonth);
                if (validInput == 0) // means validInput = false
                    continue;
            }

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                cout << "Year (yyyy): ";
                getline(cin, h_sYear);
                validInput = checknum(h_sYear);
                if (validInput == 0) // means validInput = false
                    continue;
            }

            start = h_sYear + "/" + h_sMonth + "/" + h_sDay;

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                // user input end day
                cout << "Enter your house end date\n";
                cout << "Day (dd): ";
                getline(cin, h_eDay);
                validInput = checknum(h_eDay);
                if (validInput == 0) // means validInput = false
                    continue;
            }

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                cout << "Month (mm): ";
                getline(cin, h_eMonth);
                validInput = checknum(h_eMonth);
                if (validInput == 0) // means validInput = false
                    continue;
            }

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                // user input start day
                cout << "Year (yyyy): ";
                getline(cin, h_eYear);
                validInput = checknum(h_eYear);
                if (validInput == 0) // means validInput = false
                    continue;
            }

            end = h_eYear + "/" + h_eMonth + "/" + h_eDay;

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                cout << "Consunming points per day: ";
                getline(cin, credit);
                validInput = checknum(credit);
                if (validInput == 0) // means validInput = false
                    continue;
            }

            validInput = false; // set validInput back to false for next while loop
            while (validInput != true)
            {
                cout << "Minimum required occupier rating (-10 -> 10): ";
                getline(cin, rating);
                validInput = checkRating(rating);
                if (validInput == 0) // means validInput = false
                    continue;
            }
            this->houseOwned->setData(start, end, stod(rating), stod(credit));

            cout << "\nYou have successfully listed your house.\n";
            return true;
        }
        else
        {
            cerr << "\nYou have already listed your house. You can only unlist it.\n";
            return false;
        }
    }
    else
    {
        cerr << "\nYou need to add your house first\n";
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

            cout << "\nYou have successfully unlisted your house.\n";
            return true;
        }
        else
        {
            cerr << "\nYou have already unlisted your house. You can only list it.\n";
            return false;
        }
    }
    else
    {
        cerr << "\nYou need to add your house first\n";
        return false;
    }
};

void Member::sendRequest(int num)
{
    if (num < 0 || num > this->availableHouses.size())
    {
        cout << "\nInvalid input\n";
        return;
    }

    if (this->houseOccupied == NULL)
    {
        this->availableHouses.at(num)->addRequest(this, this->startDate, this->endDate, this->numDays);
        this->requestSentList.push_back(new Request(this, this->availableHouses.at(num), this->startDate, this->endDate, this->numDays));
        cout << "\nYour request has successlly sent to " << this->availableHouses.at(num)->owner->username << "\n";
    }
    else
    {
        cerr << "\nYou cannot occupy more than 1 house\n";
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

    cout << "\nThere are " << list.size() << " people request to rent this house: \n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << "\n"
             << i + 1 << ". " << list.at(i)->sender->username << "\n";
        cout << "- Full name: " << list.at(i)->sender->fullName << "\n";
        cout << "- Contact number: " << list.at(i)->sender->phone << "\n";
        cout << "- Rating: " << Rating::calculateScores(list.at(i)->sender->ratings) << "\n";
        cout << "- Request to rent for " << list.at(i)->numDay << " days, from " << list.at(i)->startDate << " to " << list.at(i)->endDate << "\n";
    }
    return true;
};

bool Member::acceptRequest(int num)
{

    if (num < 0 || num > this->houseOwned->requestList.size())
    {
        cout << "\nInvalid input\n";
        return false;
    }

    vector<Request *> list = this->houseOwned->requestList; // requests sent to this house
    Request *temp = this->houseOwned->requestList.at(num);  // request selected by owner

    for (Member *occupier : this->houseOwned->occupierList)
    {
        if (this->houseOwned->requestList.at(num)->sender == occupier)
        {
            cout << "\nThis request has been accepted before\n";
            return false;
        }
    }

    this->houseOwned->addOccupier(this->houseOwned->requestList.at(num)->sender);
    this->houseOwned->requestList.at(num)->sender->houseOccupied = this->houseOwned;

    // for (int i = 0; i < this->houseOwned->requestList.at(num)->sender->requestSentList.size(); i++)
    // {
    //     this->houseOwned->requestList.at(num)->sender->requestSentList.pop_back();
    // }

    this->houseOwned->requestList.at(num)->sender->startDate = this->houseOwned->requestList.at(num)->startDate;
    this->houseOwned->requestList.at(num)->sender->endDate = this->houseOwned->requestList.at(num)->endDate;

    this->houseOwned->requestList.at(num)->sender->credit -= this->houseOwned->requestList.at(num)->numDay * this->houseOwned->consummingCredits;
    this->credit += this->houseOwned->requestList.at(num)->numDay * this->houseOwned->consummingCredits;

    this->houseOwned->requestList.at(num)->sender->requestSentList.clear();
    
    // Check requestList of house to delete overlapped time request
    int size = 0;
    for (int i = size; i < this->houseOwned->requestList.size(); i = size)
    {
        if ((this->houseOwned->requestList.at(i)->startDate >= temp->startDate) && (this->houseOwned->requestList.at(i)->startDate < temp->endDate) || (this->houseOwned->requestList.at(i)->endDate > temp->startDate) && (this->houseOwned->requestList.at(i)->endDate <= temp->endDate))
        {
            this->houseOwned->requestList.erase(this->houseOwned->requestList.begin() + i);
        }
        else if ((this->houseOwned->requestList.at(i)->startDate <= temp->startDate) && (this->houseOwned->requestList.at(i)->endDate >= temp->endDate))
        {
            this->houseOwned->requestList.erase(this->houseOwned->requestList.begin() + i);
        }
        else
        {
            size++;
        }
    }

    cout << "\nYou have accepted this request\n";
    return true;
};

void Member::showRequestList()
{
    vector<Request *> list = this->requestSentList;
    cout << "\nYou have sent " << list.size() << " requests\n";

    if (list.size() > 0)
    {
        for (int i = 0; i < list.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". Owner: " << list.at(i)->house->owner->username << "\n";
            cout << "House's details: \n";
            cout << "Location: " << list.at(i)->house->city << "\n";
            cout << "Description: " << list.at(i)->house->description << "\n";
            cout << "Rating: " << Rating::calculateScores(list.at(i)->house->ratings) << "\n";
            cout << "Consuming credits: " << list.at(i)->house->consummingCredits << "\n";
            cout << "Request to rent for " << list.at(i)->numDay << " days, from " << list.at(i)->startDate << " to " << list.at(i)->endDate << "\n";
        }
    }
}

// ----------------------------------------NU------------------------------------- //

template <class T>
void Member::rate(T *object)
{
    for (Rating *r : object->ratings)
    {
        if (r->rater == this)
        {
            cerr << "\nYou can only rate once\n";
            return;
        }
    }

    if (object != NULL)
    {
        string comment, score, option;
        bool validInput = false; // set validInput back to false for next while loop
        while (validInput != true)
        {
            cout << "How many scores would you like to give (-10 -> 10)? \n";
            getline(cin, score);
            validInput = checkRating(score);
            if (validInput == 0) // means validInput = false
                continue;
        }

        cout << "Would you like to leave a comment? (Y/N) \n";
        getline(cin, option);
        if (option.compare("Y") == 0)
        {
            cout << "Please write your comment down here: \n";
            getline(cin, comment);
        }
        else
        {
            comment = "";
        }
        cout << "Thank you! \n";
        object->ratings.push_back(new Rating(this, comment, stod(score)));
    }
};

template void Member::rate(Member *);
template void Member::rate(House *);

void Member::rateMember()
{
    if (this->houseOwned == NULL)
    {
        cerr << "\nYou need to add your house first\n";
    }
    else if (!this->houseOwned->occupierList.empty())
    {
        string option;
        this->houseOwned->showOccupierList();
        cout << "\nPlease choose a occupier by entering a number: ";
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

// A date has day 'd', month 'm' and year 'y'
struct Date
{
    int d, m, y;
};

// To store number of days in
// all months from January to Dec.
const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

// This function counts number of
// leap years before the given date
int countLeapYears(Date d)
{
    int years = d.y;

    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (d.m <= 2)
        years--;

    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
    // multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

// This function returns number of
// days between two given dates
int getDifference(Date dt1, Date dt2)
{
    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'

    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;

    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);

    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'

    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    // return difference between two counts
    return (n2 - n1);
}

bool Member::checkAvailableHouses()
{

    this->availableHouses.clear();
    // member date select
    string m_sMonth, m_sYear, m_sDay;
    string m_eMonth, m_eYear, m_eDay;
    string city;
    bool validInput = false;
    cout << "\nPlease provide the below information to search for available houses \n";

    while (validInput != true)
    {
        // user input city
        cout << "City: ";
        getline(cin, city);
        validInput = checkCity(city);
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false;
    while (validInput != true)
    {
        // user input start day
        cout << "Enter your start date\n";
        cout << "Day (dd): ";
        getline(cin, m_sDay);
        validInput = checknum(m_sDay);
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false; // set validInput back to false for next while loop
    while (validInput != true)
    {
        // user input start day
        cout << "Month (mm): ";
        getline(cin, m_sMonth);
        validInput = checknum(m_sMonth);
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false; // set validInput back to false for next while loop
    while (validInput != true)
    {
        // user input start day
        cout << "Year (yyyy): ";
        getline(cin, m_sYear);
        validInput = checknum(m_sYear);
        if (validInput == 0) // means validInput = false
            continue;
    }
    string startDate = m_sYear + "/" + m_sMonth + "/" + m_sDay;

    validInput = false; // set validInput back to false for next while loop
    while (validInput != true)
    {
        // user input end day
        cout << "Enter your end date\n";
        cout << "Day (dd): ";
        getline(cin, m_eDay);
        validInput = checknum(m_eDay);
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false; // set validInput back to false for next while loop
    while (validInput != true)
    {
        cout << "month (mm): ";
        getline(cin, m_eMonth);
        validInput = checknum(m_eMonth);
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false; // set validInput back to false for next while loop
    while (validInput != true)
    {
        cout << "Year (yyyy): ";
        getline(cin, m_eYear);
        validInput = checknum(m_eYear);
        if (validInput == 0) // means validInput = false
            continue;
    }

    string endDate = m_eYear + "/" + m_eMonth + "/" + m_eDay;

    // get day, month, year
    int sYear = stoi(m_sYear);
    int sMonth = stoi(m_sMonth);
    int sDay = stoi(m_sDay);

    int eYear = stoi(m_eYear);
    int eMonth = stoi(m_eMonth);
    int eDay = stoi(m_eDay);

    Date date1 = {sDay, sMonth, sYear};
    Date date2 = {eDay, eMonth, eYear};

    int days = getDifference(date1, date2);

    if (endDate < startDate)
    {
        cout << "\nInvalid date\n";
        return false;
    }

    double score = Rating::calculateScores(this->ratings);

    for (Member *m : DataHandler::memberList)
    {
        if (m == this)
        {
            continue;
        }
        if (m->houseOwned != NULL)
        {
            string HouseStart = m->houseOwned->startDate;
            string HouseEnd = m->houseOwned->endDate;
            if (city == m->houseOwned->city)
            {
                if ((HouseStart <= startDate && startDate < HouseEnd) && (HouseStart < endDate && endDate <= HouseEnd))
                {
                    if (this->credit >= m->houseOwned->consummingCredits * days)
                    {
                        if (score >= m->houseOwned->minOccRating)
                        {
                            this->availableHouses.push_back(m->houseOwned);
                            // continue;
                        }
                    }
                }
            }
        }
    }

    if (!this->availableHouses.empty())
    {
        cout << "\nThere are " << this->availableHouses.size() << " houses available to rent: \n";
        this->startDate = startDate;
        this->endDate = endDate;
        this->numDays = days;

        for (int i = 0; i < availableHouses.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". Owner: " << availableHouses.at(i)->owner->username << "\n";
            cout << "Rating: " << Rating::calculateScores(availableHouses.at(i)->ratings) << "\n";
            cout << "Credit required per day: " << availableHouses.at(i)->consummingCredits << "\n";
            cout << "Description: " << availableHouses.at(i)->description << "\n";
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
void Member::viewHouseReviews(int num)
{
    if (num < 0 || num > this->availableHouses.size())
    {
        cout << "\nInvalid input\n";
        return;
    }

    vector<Rating *> list = this->availableHouses.at(num)->ratings;

    if (list.size() > 0)
    {
        cout << "\nThere are " << list.size() << " reviews about this house\n";
        for (int i = 0; i < this->availableHouses.at(num)->ratings.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". " << list.at(i)->rater->username << "\n";
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
    if (num < 0 || num > this->houseOwned->requestList.size())
    {
        cout << "\nInvalid input\n";
        return;
    }

    vector<Rating *> list = this->houseOwned->requestList.at(num)->sender->ratings;

    if (list.size() > 0)
    {
        cout << "\nThere are " << list.size() << " reviews about this Member\n";
        for (int i = 0; i < list.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". " << list.at(i)->rater->username << "\n";
            cout << "Score: " << list.at(i)->score << "\n";
            cout << "Comment: " << list.at(i)->comment << "\n";
        }
    }
    else
    {
        cerr << "There are no reviews\n";
    }
};
