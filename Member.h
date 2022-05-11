#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

class Member
{
private:
    string username, password, fullName;
    int phone, credit = 500;
    House *houseOwned, *houseOccupied;
    vector<House *> availableHouses;
    vector<Request *> requestSentList;
    vector<Rating *> ratings;

    Member(){};

    Member(string username, string password, string fullName, int phone)
    {
    }

    static bool login(){};

    void listHouse(){};

    void unlistHouse(){};

    void sendRequest(House *house, string start, string end){};

    bool viewRequest(){};

    // void acceptRequest(Member *member)

    // };

    void cancelRequest(){

    };

    // ----------------------------------------NU------------------------------------- //

    void rate(Member *member){};

    void rate(House *house)
    {
    }

    // Check the houses matched with date, city, rating and credit of user
    // then add all of them to availableHouses attribute
    void checkAvailableHouses(Member *member){};

    // Display review of selected house in the availableHouses attribute
    void viewReviews(House *house){

    };
    
    friend class House;
    friend class Rating;
    friend class Request;
};

vector<Member *> memberList;