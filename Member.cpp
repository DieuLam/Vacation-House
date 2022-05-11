#include "Member.h"
#include "Rating.h"
#include "House.h"
#include "Request.h"
#include <algorithm>
#include <iostream>
#include <string>

Member::Member(){};

Member::Member(string username, string password, string fullName, int phone)
{
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->phone = phone;
}

bool Member::login()
{
    string tempUsername;
    string tempPass;
    cout << "Please enter your username: ";
    cin >> tempUsername;
    cout << "Please enter your password: ";
    cin >> tempPass;

    for (Member *m : memberList)
    {
        if ((m->username).compare(tempUsername) == 0)
        {
            if ((m->password).compare(tempPass) == 0)
            {
                cout << "Login successfully!";
                return true;
            }
            else
            {
                cerr << "Incorrect password!";
                return false;
            }
        }
    }

    cerr << "Account does not exist";
    return false;
};

void Member::listHouse()
{
    string start, end;
    double rating, credit;

    cout << "Please set the availability of your house \n\n";
    cout << "Start date (dd/mm/yy): ";
    cin >> start;
    cout << "End date (dd/mm/yy): ";
    cin >> end;
    cout << "Consunming points per day: ";
    cin >> credit;
    cout << "Minimum required occupier rating (0 -> 10): ";
    cin >> rating;

    this->houseOwned->setData(start, end, rating, credit);
};

void Member::unlistHouse()
{
    // this->houseOwned->setAvailability(this);
    this->houseOwned->setData(NULL, NULL, 0.0, 0.0);
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

// void Member::acceptRequest(Member *member)
// {
//     vector<Request *> list = this->houseOwned->requestList;
//     if (std::find(list.begin(), list.end(), member) != list.end())
//     {
//         this->houseOwned->addOccupier(member);
//         this->houseOwned->resetDate(member->startDate);
//         member->houseOccupied = this->houseOwned;
//     }

//     // if ()
// };

void Member::cancelRequest(){

};

// ----------------------------------------NU------------------------------------- //

void Member::rate(Member *member)
{
    double score;
    string comment;
    cout << "How many scores would you like to give? \n";
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
    cout << "How many scores would you like to give? \n";
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

//reverse input
    // void reverseStr(string& str){
    //     int n = str.length();
    
    //     // Swap character starting from two
    //     // corners
    //     for (int i = 0; i < n / 2; i++)
    //         std::swap(str[i], str[n - i - 1]);
    // }

// Check the houses matched with date, city, rating and credit of user
// then add all of them to availableHouses attribute
void Member::checkAvailableHouses(Member *member)
{
    //member date select
        string startDate;
        string endDate;
        char fill = '/';
        int m_sMonth, m_sYear, m_sDay;
        int m_eMonth, m_eYear, m_eDay;


        //user input start day
        cout << "Please provide the below information to search for available houses \n\n";
        cout << "Start date (yyyy/mm/dd): ";
        cin >> startDate;

        //user input end day
        cout << "End date (yyyy/mm/dd): ";
        cin >> endDate;


        //get day, month, year
        // m_sYear = stoi(startDate.substr(0,2));
        // m_sMonth = stoi(startDate.substr(3,2));
        // m_sDay = stoi(startDate.substr(6));

        // m_eYear = stoi(endDate.substr(0,2));
        // m_eMonth = stoi(endDate.substr(3,2));
        // m_eDay = stoi(endDate.substr(6));

    std::fstream houseInfoFile;
    houseInfoFile.open("houseInfo.txt",std::ios::in); //ios::in to open file performing read operations
    string temp;
    string delimeter = "|";
    while(getline(houseInfoFile,temp)){//save line to string temp
        size_t pos = 0;
        string subString;
        vector<string> printInfo; //save each element into a vector
        while ((pos = temp.find (delimeter)) != std::string::npos){ //use find() here to get position of delimiters
            subString = temp.substr(0,pos); //subString is equals to all string up to delimiter '|'
            printInfo.push_back(subString); //put the subString into the vector
            temp.erase(0,pos + delimeter.length()); //delete the subString from the line so the next subString won't be repeated
        }
        printInfo.push_back(temp); //since temp should now only have the last element, push it 

        for (int i = 0; i < printInfo.size(); i++) {
            if(endDate < startDate) {
                cout << "invalid date!!!";
                return;
            } else {
                if ((printInfo[4] >= startDate && startDate <= printInfo[5]) && (printInfo[4] >= endDate && endDate <= printInfo[5])) {
                    cout << printInfo[0];
                }
            }
        }
    }
    houseInfoFile.close();
};

// Display review of selected house in the availableHouses attribute
void Member::viewReviews(House *house){

};

