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
class Request;

class Rating
{
    private:
    Member *rater;
    string comment;
    double score;

    public:
    Rating () {};

    Rating(Member *m, string comment, double score) {
        this->rater = m;
        this->comment = comment;
        this->score = score;
    }

    friend double calculateScores(vector<Rating *> ratings);
};

class House
{
private:
    string city, description, startDate, endDate;
    double consummingCredits, minOccRating;
    Member *owner;
    vector<Member *> occupierList;
    vector<Rating *> ratings;
    vector<Request *> requestList;

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
    };

    void resetDate(string date)
    {
        this->startDate = date;
    };

    void addOccupier(Member *member)
    {
        if (member != this->owner)
        {
            this->occupierList.push_back(member);
        }
    };

    void addRequest(Member *member, string start, string end)
    {
        if (member != this->owner)
        {
            this->requestList.push_back(new Request (member, this, start, end));
        }
    };

    friend double calculateScores();
    friend class Member;
};


class Request {
    private:
    Member *sender;
    House *house;
    string startDate;
    string endDate;

    public:

    Request() {};

    Request(Member *sender, House *house, string start, string end) {
        this->sender = sender;
        this->house = house;
        this->startDate = start;
        this->endDate = end;
    }

    friend class Member;
    friend class House;
};

vector<Member *> memberList;

// --------------------------------------Trang & Diu---------------------------------------//

class Member
{
private:
    string username, password, fullName;
    int phone, credit = 500;
    vector<Rating *> ratings;
    House *houseOwned, *houseOccupied;
    vector<House *> availableHouses;
    vector<Request *> requestSentList;

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

    void unlistHouse()
    {
        // this->houseOwned->setAvailability(this);
        this->houseOwned->setData(NULL, NULL, 0.0, 0.0);
    };

    void sendRequest(House *house, string start, string end)
    {
        if (std::find(availableHouses.begin(), availableHouses.end(), house) != availableHouses.end())
        {
            house->addRequest(this, start, end);
            this->requestSentList.push_back(new Request(this, house, start, end));
        }
    };

    bool viewRequest()
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
            cout << "- Rating: " << calculateScores(list[i]->sender->ratings) << "\n";
            cout << "- Request to rent from " << list[i]->startDate << " to " << list[i]->endDate << "\n";
        }
        return true;
    };

    // void acceptRequest(Member *member)
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

    void cancelRequest(){

    };

    // ----------------------------------------NU------------------------------------- //

    void rate(Member *member)
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
        } else {
            comment = "";
        }
        cout << "Thank you! \n\n";
        member->ratings.push_back(new Rating(this, comment, score));
    }; 
    
    void rate(House *house)
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
        } else {
            comment = "";
        }
        cout << "Thank you! \n\n";
        house->ratings.push_back(new Rating(this, comment, score));
    }

    

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

    friend double calculateScores(vector<Rating *> ratings);

    friend class Request;
    friend class House;
};

double calculateScores(vector<Rating *> ratings)
{
    double sum = 0;
    for (Rating *r : ratings)
    {
        sum += r->score;
    }
    return sum / ratings.size();
}

int main()
{

    Member M1("trang", "trang", "minh trang", 123), M2("diu", "diu", "diu lam", 456), M3("nu", "nu", "nule", 789);

    House H1(&M1, "Hanoi", "This is a house1"), H2(&M2, "HCM", "This is a house2");

    memberList.push_back(&M1);
    memberList.push_back(&M2);
    memberList.push_back(&M3);

    M1.listHouse();

    return 0;
}