#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

// --------------------------------------TRANG----------------------------------------//
class Member;

class House
{
private:
    string city, description, startDate, endDate;
    double consummingCredits, minOccRating;
    Member *owner, *occupier;
    bool availabity = false;
    vector<Member *> requests, occupierList;
    vector<double> scores;
    vector<string> comments;

public:
    House(){};

    House(Member *owner, string city, string description)
    {
        this->owner = owner;
        this->city = city;
        this->description = description;
    };

    void setData(string startDate, string endDate, int minRating, double conCredits)
    {
        this->startDate = startDate;
        this->endDate = endDate;
        this->minOccRating = minRating;
        this->consummingCredits = conCredits;
        this->availabity = true;
    };

    void addOccupier(Member *member)
    {
        if (member != this->owner)
        {
            this->occupier = member;
        }
    };

    void setAvailability(Member *member, bool status)
    {
        if (checkIfOwner(member)) {
        this->availabity = status;
        }
    };

    vector<Member *> getRequestList(Member *member) {
        if (checkIfOwner(member)) {
            return this->requests;
        }
    };

    bool checkIfOwner(Member *member) {
        if (member == this->owner) {
            return true;
        } else {
            return false;
        }
    };

    friend double calculateScores();

    // friend class Member;
};

vector<Member *> memberList;

// --------------------------------------SON---------------------------------------//

class User
{

public:
    void viewHouse(){

    };

    void registerToBeMember(){

    };

    User(){};
};

// --------------------------------------Trang & Diu---------------------------------------//

class Member
{
private:
    string username, password, fullName;
    int phone, credit = 500;
    vector<double> ratingScores;
    vector<string> comments;
    House *houseOwned, *houseOccupied;
    vector<House *> availableHouses;

public:
    Member(){};

    Member(string username, string password, string fullName, int phone)
    {
        this->username = username;
        this->password = password;
        this->fullName = fullName;
        this->phone = phone;
    }

    static bool login()
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

    void listHouse()
    {
        string start, end;
        int rating;
        double credit;

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

    void unlistHouse()
    {
        this->houseOwned->setAvailability(this, false);
    };

    void sendRequest(House *house)
    {
        if (std::find(availableHouses.begin(), availableHouses.end(), house) != availableHouses.end())
        {
            house->addOccupier(this);
        }
    };

    bool viewRequest(){
        vector<Member *> list = this->houseOwned->getRequestList(this);

        if (list.size() == 0) {
            cout << "No occupying requests for this house";
            return false;
        }

        cout << "There are " << list.size() << " people request to rent this house: \n\n";
        for (int i = 0; i < list.size(); i++) {
            cout << i << ". " << list[i]->username << "\n";
            cout << "- Full name: " << list[i]->fullName << "\n";
            cout << "- Contact number: " << list[i]->phone << "\n";
            cout << "- Rating: " << calculateScores(list[i]->ratingScores) << "\n";
        }
        return true;   
    };

    void manageRequest(){

    };

    void cancelRequest(){

    };

    // ----------------------------------------NU------------------------------------- //

    void rateOccupier(Member *member){

    };

    void rateHouse(House *house){

    };

    // Check the houses matched with date, city, rating and credit of user
    // then add all of them to availableHouses attribute
    void checkAvailableHouses(Member *member)
    {
        string start, end, city;
        cout << "Please provide the below information to search for available houses \n\n";
        cout << "Start date: ";
        cin >> start;
        cout << "End date: ";
        cin >> end;
        cout << "City: ";
        cin >> city;

        // for (Member *m : memberList)
        // {
        //     if ((m->houseOwned).compare(tempUsername) == 0)
        //     {
        //     }
        // };
    };

    // Display review of selected house in the availableHouses attribute
    void viewReviews(House *house){

    };

    friend double calculateScores(vector<double> list);
};

double calculateScores(vector<double> list) {
    double sum = 0;
    for (int s : list) {
        sum += s;
    }
    return sum/list.size();
}

//---------------------------------------------------SON---------------------------------------------//

class Admin
{
private:
    string username, password;

public:
    void login()
    {
    }

    void viewMembers()
    {
    }

    void viewHouse()
    {
    }
};

int main()
{
    User C1;

    Member M1("trang", "trang", "minh trang", 123), M2("diu", "diu", "diu lam", 456), M3("nu", "nu", "nule", 789);

    House H1(&M1, "Hanoi", "This is a house1"), H2(&M2, "HCM", "This is a house2");

    memberList.push_back(&M1);
    memberList.push_back(&M2);
    memberList.push_back(&M3);

    M1.listHouse();


    return 0;
}