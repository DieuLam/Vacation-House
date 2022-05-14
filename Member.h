#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

class Rating;
class House;
class Request;

class Member
{
public:
    string username, password, fullName, phone;
    double credit = 0.0;
    House *houseOwned = NULL, *houseOccupied = NULL;
    vector<House *> availableHouses;
    vector<Request *> requestSentList;
    vector<Rating *> ratings;
public:
    Member();
    
    Member(string username, string password, string fullName, string phone);

    static Member* login();

    void addHouse();

    bool listHouse();

    bool unlistHouse();

    void sendRequest(int num, string start, string end);

    bool viewRequest();

    bool acceptRequest(Request *request);

    void cancelRequest();

    string Member::getDate(string start, string end);

    // ----------------------------------------NU------------------------------------- //

    void rate(Member *member);

    void rate(House *house);

    // Check the houses matched with date, city, rating and credit of user
    // then add all of them to availableHouses attribute
    bool checkAvailableHouses();

    // Display review of selected house in the availableHouses attribute
    void viewReviews(House *house);

    friend class House;
    friend class Rating;
    friend class Request;
    friend class DataHandler;
    friend class User;
};