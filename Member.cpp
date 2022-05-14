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
        cout << "Please provide the location of your house: ";
        getline(cin, location);
        cout << "Please provide description for your house: ";
        getline(cin, description);
        this->houseOwned = new House(this, location, description);

        cout << "You have successfully added a house.\n";
    }
    else
    {
        cerr << "You cannot have more than 1 house\n";
    }
};

bool Member::listHouse()
{
    if (this->houseOwned != NULL)
    {
        if (this->houseOwned->startDate == "")
        {
            string start, end;
            double rating, credit;

            cout << "Please set the availability of your house \n\n";
            cout << "Start date (yyyy/mm/dd): ";
            cin >> start;
            cout << "End date (yyyy/mm/dd): ";
            cin >> end;
            cout << "Consunming points per day: ";
            cin >> credit;
            cout << "Minimum required occupier rating (0 -> 10): ";
            cin >> rating;
            this->houseOwned->setData(start, end, rating, credit);

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

void Member::sendRequest(House *house, string start, string end)
{
    if (std::find(availableHouses.begin(), availableHouses.end(), house) != availableHouses.end())
    {
        house->addRequest(this, start, end);
        this->requestSentList.push_back(new Request(this, house, start, end));
    }
};

bool Member::viewRequest()
{
    vector<Request *> list = this->houseOwned->requestList;

    if (list.size() == 0)
    {
        cout << "No occupying requests for this house";
        return false;
    }

    cout << "There are " << list.size() << " people request to rent this house: \n\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << i << ". " << list[i]->sender->username << "\n";
        cout << "- Full name: " << list[i]->sender->fullName << "\n";
        cout << "- Contact number: " << list[i]->sender->phone << "\n";
        cout << "- Rating: " << Rating::calculateScores(list[i]->sender->ratings) << "\n";
        cout << "- Request to rent from " << list[i]->startDate << " to " << list[i]->endDate << "\n";
    }
    return true;
};

bool Member::acceptRequest(Request *request)
{
    vector<Request *> list = this->houseOwned->requestList;
    if (std::find(list.begin(), list.end(), request) != list.end())
    {
        this->houseOwned->addOccupier(request->sender);
        this->houseOwned->resetDate(request->startDate);
        request->sender->houseOccupied = this->houseOwned;
        request->sender->requestSentList.clear();

        // Check requestList of house to delete overlapped time request
        return true;
    }

    return false;
};

void Member::cancelRequest(){

};

// ----------------------------------------NU------------------------------------- //

void Member::rate(Member *member)
{
    double score;
    string comment;
    cout << "How many scores would you like to give (0 -> 10)? \n";
    cin >> score;
    cout << "Would you like to leave a comment? (Y/N) \n";
    cin >> comment;
    if (comment.compare("Y") == 0)
    {
        cout << "Please write your comment down here \n\n";
        cin >> comment;
    }
    else
    {
        comment = "";
    }
    cout << "Thank you! \n\n";
    member->ratings.push_back(new Rating(this, comment, score));
};

void Member::rate(House *house)
{
    double score;
    string comment;
    cout << "How many scores would you like to give (0 -> 10)? \n";
    cin >> score;
    cout << "Would you like to leave a comment? (Y/N) \n";
    cin >> comment;
    if (comment.compare("Y") == 0)
    {
        cout << "Please write your comment down here \n\n";
        cin >> comment;
    }
    else
    {
        comment = "";
    }
    cout << "Thank you! \n\n";
    house->ratings.push_back(new Rating(this, comment, score));
}

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

// Check the houses matched with date, city, rating and credit of user
// then add all of them to availableHouses attribute
void Member::checkAvailableHouses(Member *member)
{
    // member date select
    string startDate;
    string endDate;
    char fill = '/';
    int m_sMonth, m_sYear, m_sDay;
    int m_eMonth, m_eYear, m_eDay;
    string city;

    cout << "Please provide the below information to search for available houses \n\n";
    // user input city
    cout << "City: ";
    cin >> city;
    // user input start day
    cout << "Start date (yyyy/mm/dd): ";
    cin >> startDate;
    // user input end day
    cout << "End date (yyyy/mm/dd): ";
    cin >> endDate;

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
        if (m == member)
        {
            continue;
        }
        string HouseStart = m->houseOwned->startDate;
        string HouseEnd = m->houseOwned->endDate;

        if (m->houseOwned != NULL)
        {
            if (endDate < startDate)
            {
                cout << "invalid";
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

    for (House *h : availableHouses)
    {
        cout << h->owner->username << "\n";
    }
};

// Display review of selected house in the availableHouses attribute
void Member::viewReviews(House *house){

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
