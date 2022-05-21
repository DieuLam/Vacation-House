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
        bool validInput = false;
        string location, description;
        cout << "\nPlease provide information of your house: \n";

        while (validInput != true)
        {
            // user input city
            cout << "Location (Saigon/Hanoi/Danang): ";
            getline(cin, location);
            validInput = checkCity(location);
        }

        cout << "Description: ";
        getline(cin, description);
        this->houseOwned = new House(this, location, description, "", "", 0, 0);

        DataHandler::addHouse(houseOwned);

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
    if (this->houseOccupied == NULL)
    {
        this->availableHouses.at(num)->addRequest(this, this->startDate, this->endDate, this->numDays);
        this->requestSentList.push_back(new Request(this, this->availableHouses.at(num), this->startDate, this->endDate, this->numDays));
        cout << "Your request has successlly sent to " << this->availableHouses.at(num)->owner->username << "\n";
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

    cout << "\nThere are " << list.size() << " people request to rent this house: \n\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << i + 1 << ". " << list.at(i)->sender->username << "\n";
        cout << "- Full name: " << list.at(i)->sender->fullName << "\n";
        cout << "- Contact number: " << list.at(i)->sender->phone << "\n";
        cout << "- Rating: " << Rating::calculateScores(list.at(i)->sender->ratings) << "\n";
        cout << "- Request to rent from " << list.at(i)->startDate << " to " << list.at(i)->endDate << "\n";
    }
    return true;
};

bool Member::acceptRequest(int num)
{
    vector<Request *> list = this->houseOwned->requestList;
    for (Member *occupier : this->houseOwned->occupierList) {
        if (list.at(num)->sender == occupier) {
            cout << "\nThis request has been accepted before\n";
            return false;
        }
    }

    if (!list.empty())
    {
        this->houseOwned->addOccupier(list.at(num)->sender);
        // this->houseOwned->resetDate(list.at(num)->startDate);
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

        list.at(num)->sender->credit -= list.at(num)->sender->numDays * this->houseOwned->consummingCredits;
        this->credit += list.at(num)->sender->numDays * this->houseOwned->consummingCredits;

        cout << "You have accepted this request\n";
        return true;
    }

    return false;
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

    int date1[3] = {sDay, sMonth, sYear};
    int date2[3] = {eDay, eMonth, eYear};

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
                cout << "\nInvalid date\n";
            }
            else
            {
                if (city == m->houseOwned->city)
                {
                    cout << "1";
                    if ((HouseStart <= startDate && startDate < HouseEnd) && (HouseStart < endDate && endDate <= HouseEnd))
                    {
                        cout << "2";
                        if (m->houseOwned->consummingCredits * days <= this->credit)
                        {
                            cout << "3";
                            if (score >= m->houseOwned->minOccRating)
                            {
                                cout << "4";
                                this->availableHouses.push_back(m->houseOwned);
                            }
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
    vector<Rating *> list = this->availableHouses.at(num)->ratings;
    if (list.size() > 0)
    {
        cout << "\nThere are " << list.size() << " reviews about this house\n";
        for (int i = 0; i < this->availableHouses.at(num)->ratings.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ". " << list.at(i)->rater << "\n";
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
                 << i + 1 << ". " << list.at(i)->rater << "\n";
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
