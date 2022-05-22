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

// display info of a member
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
        cout << "- House occupied: " << this->houseOccupied->owner->username << "\n"; // username of the owner of the house that this member occupies
    }
    else
    {
        cout << "- House occupied: None \n";
    }
}

// display info of a house
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

        // display all occupiers of the house
        for (int i = 0; i < this->houseOwned->occupierList.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". " << this->houseOwned->occupierList.at(i)->username << "\n";
            cout << "Time: " << this->houseOwned->occupierList.at(i)->startDate << " to " << this->houseOwned->occupierList.at(i)->endDate << "\n";
        }
    }
    else
    {
        cerr << "\nYou need to add your house first\n"; // if member have no house to display
    }
};

// member login
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
        if ((m->username).compare(tempUsername) == 0) // check if member exists
        {
            if ((m->password).compare(tempPass) == 0) // check if password correct
            {
                cout << "\nLogin successfully!\n";
                return m;
            }
            else
            {
                cerr << "\nIncorrect password!\n";
                return NULL;
            }
        }
    }

    cerr << "\nAccount does not exist\n";
    return NULL;
};

// add a house to member
void Member::addHouse()
{
    if (this->houseOwned == NULL) // check if member already had a house
    {
        bool validInput = false;
        string location, description;

        cout << "\nPlease provide information of your house: \n";

        while (validInput != true)
        {
            // user input city
            cout << "Location (Saigon/Hanoi/Da Nang): ";
            getline(cin, location);
            validInput = checkCity(location); // check if the city valid
        }

        cout << "Description: ";
        getline(cin, description);
        this->houseOwned = new House(this, location, description, "", "", 0, 0); // create a house and assign to the member
        cout << "\nYou have successfully added a house.\n";

        DataHandler::addHouse(houseOwned); // add house to the system list
    }
    else
    {
        cerr << "\nYou cannot have more than 1 house\n";
    }
};

// member can list house for rent
bool Member::listHouse()
{
    if (this->houseOwned != NULL) // check if member have a house to list
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

            start = h_sYear + "/" + h_sMonth + "/" + h_sDay; // combine to get start date as format yyyy/mm/dd

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

            end = h_eYear + "/" + h_eMonth + "/" + h_eDay; // combine to get end date as format yyyy/mm/dd

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

            this->houseOwned->setData(start, end, stod(rating), stod(credit)); // set data to the member's house
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

// member can unlist the house
bool Member::unlistHouse()
{
    if (this->houseOwned != NULL) // check if member has a house to unlist
    {
        if (this->houseOwned->startDate != "") // check if house is already listed
        {
            this->houseOwned->setData("", "", 0.0, 0.0); // delete all listed data

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

// send request to the available houses
void Member::sendRequest(int num)
{
    if (num < 0 || num > this->availableHouses.size()) // check if the user input in the range
    {
        cout << "\nInvalid input\n";
        return;
    }

    if (this->houseOccupied == NULL) // check if member hasn't occupied a house
    {
        this->availableHouses.at(num)->addRequest(this, this->startDate, this->endDate, this->numDays);                                   // add request to the house's request list
        this->requestSentList.push_back(new Request(this, this->availableHouses.at(num), this->startDate, this->endDate, this->numDays)); // add request to the sender's request list
        cout << "\nYour request has successlly sent to " << this->availableHouses.at(num)->owner->username << "\n";
    }
    else
    {
        cerr << "\nYou cannot occupy more than 1 house\n";
    }
};

// view all requests that have been sent to member's house
bool Member::viewRequest()
{
    if (this->houseOwned == NULL) // check if member has a house
    {
        cerr << "\nYou have to add your house first\n";
        return false;
    }

    vector<Request *> list = this->houseOwned->requestList; // copy request list of the house

    if (list.size() == 0) // check if there's any request for this house
    {
        cout << "\nNo occupying requests for this house\n";
        return false;
    }

    // display all request
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

// accept a request
bool Member::acceptRequest(int num)
{
    if (num < 0 || num > this->houseOwned->requestList.size()) // check if user input in the range
    {
        cout << "\nInvalid input\n";
        return false;
    }

    vector<Request *> list = this->houseOwned->requestList; // requests sent to this house
    Request *temp = this->houseOwned->requestList.at(num);  // request selected by owner

    this->houseOwned->addOccupier(this->houseOwned->requestList.at(num)->sender);    // set occupier of the house as the requester
    this->houseOwned->requestList.at(num)->sender->houseOccupied = this->houseOwned; // set the requester's occupied house as this house

    this->houseOwned->requestList.at(num)->sender->startDate = this->houseOwned->requestList.at(num)->startDate; // set start date of requester to the request's start date
    this->houseOwned->requestList.at(num)->sender->endDate = this->houseOwned->requestList.at(num)->endDate;     // set end date of requester to the request's start date

    this->houseOwned->requestList.at(num)->sender->credit -= this->houseOwned->requestList.at(num)->numDay * this->houseOwned->consummingCredits; // subtract credits from the occupier's credit
    this->credit += this->houseOwned->requestList.at(num)->numDay * this->houseOwned->consummingCredits;                                          // add credits from the house owner's credit

    this->houseOwned->requestList.at(num)->sender->requestSentList.clear(); // delete all requests that have been sent by this occupier

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

// display all requests that have been sent by this member
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

template <class T>
void Member::rate(T *object) // accept Member and House object
{
    for (Rating *r : object->ratings) // loop to check if the member have already rate this house/member
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
            validInput = checkRating(score); // check if user input is valid
            if (validInput == 0)             // means validInput = false
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
        object->ratings.push_back(new Rating(this, comment, stod(score))); // add new rating to current object
    }
};

template void Member::rate(Member *);
template void Member::rate(House *);

// member rate another occupiers of their house
void Member::rateMember()
{
    if (this->houseOwned == NULL) // check if member have a house
    {
        cerr << "\nYou need to add your house first\n";
    }
    else if (!this->houseOwned->occupierList.empty()) // check if there's any occupier to rate
    {
        string option;
        this->houseOwned->showOccupierList(); // display a list of occupiers for user to select which one to rate
        cout << "\nPlease choose a occupier by entering a number: ";
        getline(cin, option);
        this->rate<Member>(this->houseOwned->occupierList.at(stoi(option) - 1)); // call rate function with parameter as Member object
    }
    else
    {
        cerr << "\nYour house has not been rented by anyone\n";
    }
};

// member rate house they have occupy
void Member::rateHouse()
{
    if (this->houseOccupied != NULL) // check if member have occupy any house
    {
        this->rate<House>(this->houseOccupied); // call function rate with a parameter as a House
    }
    else
    {
        cerr << "\nYou have not occupied any house\n";
    }
};

// display review of selected house in the availableHouses attribute
void Member::viewHouseReviews(int num)
{
    if (num < 0 || num > this->availableHouses.size()) // check if user input is in the range
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

// display review of the member who request to rent this member house
void Member::viewMemberReviews(int num)
{
    if (num < 0 || num > this->houseOwned->requestList.size()) // check if user input is in the range
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

//--------------------------- calc day between for checkAvailableHouses method ----------------------------------------//

// A date has day 'd', month 'm' and year 'y'
struct Date
{
    int d, m, y;
};

// To store number of days in all months from January to Dec.
const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

// This function counts number of leap years before the given date
int countLeapYears(Date d)
{
    int years = d.y;

    // Check if the current year needs to be
    // considered for the count of leap years
    // or not
    if (d.m <= 2)
        years--;

    // A year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
    // multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

// This function returns number of days between two given dates
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

// display houses matched with user's search
bool Member::checkAvailableHouses()
{
    this->availableHouses.clear(); // reset available house lists 
     
    // member date select
    string m_sMonth, m_sYear, m_sDay;
    string m_eMonth, m_eYear, m_eDay;
    string city;
    bool validInput = false;

    cout << "\nPlease provide the below information to search for available houses \n";

    while (validInput != true)
    {
        // user input city
        cout << "City (Saigon/Hanoi/Da Nang): ";
        getline(cin, city);
        validInput = checkCity(city); // check if the city is valid
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false; // set validInput back to false for next while loop
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

    string startDate = m_sYear + "/" + m_sMonth + "/" + m_sDay; // start date with the format yyyy/mm/dd

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

    string endDate = m_eYear + "/" + m_eMonth + "/" + m_eDay; // end date with the format yyyy/mm/dd

    // get day, month, year
    int sYear = stoi(m_sYear);
    int sMonth = stoi(m_sMonth);
    int sDay = stoi(m_sDay);

    int eYear = stoi(m_eYear);
    int eMonth = stoi(m_eMonth);
    int eDay = stoi(m_eDay);

    Date date1 = {sDay, sMonth, sYear};
    Date date2 = {eDay, eMonth, eYear};

    int days = getDifference(date1, date2); // calculate number of days between start and end date

    if (endDate < startDate)
    {
        cout << "\nInvalid date\n";
        return false;
    }

    double score = Rating::calculateScores(this->ratings); // calculate average score from all ratings of the member

    for (Member *m : DataHandler::memberList) // loop through all the members to check for available houses
    {
        if (m == this) // if the member is the same as the one in the list
        {
            continue; // skip because a member cannot rent his/her own house
        }

        if (m->houseOwned != NULL) // check if the member has a house
        {
            string HouseStart = m->houseOwned->startDate;
            string HouseEnd = m->houseOwned->endDate;

            // check if the date user selected is overlapped with any of the occupiers of this house
            for (Member *occupier : m->houseOwned->occupierList)
            {
                if ((startDate >= occupier->startDate) && (startDate < occupier->endDate) || (endDate > occupier->startDate) && (endDate <= occupier->endDate))
                {
                    goto cnt; // skip to line 692
                }
                else if ((startDate <= occupier->startDate) && (endDate >= occupier->endDate))
                {
                    goto cnt; // skip to line 692
                }
            }

            if (city == m->houseOwned->city) // check if the city of the house matched
            {
                if ((HouseStart <= startDate && startDate < HouseEnd) && (HouseStart < endDate && endDate <= HouseEnd)) // check if the date matched
                {
                    if (this->credit >= m->houseOwned->consummingCredits * days) // check if member have enough credits to rent this house
                    {
                        if (score >= m->houseOwned->minOccRating) // check if member's rating is enough to rent this house
                        {
                            this->availableHouses.push_back(m->houseOwned); // add the house to available house list of the member
                        }
                    }
                }
            }
        }
    cnt:;
    }

    // display all available houses
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