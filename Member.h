#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
private:
    string username, password, fullName, phone, startDate, endDate;
    double credit = 0.0;
    House *houseOwned = NULL, *houseOccupied = NULL;
    vector<House *> availableHouses;
    vector<Request *> requestSentList;
    vector<Rating *> ratings;

public:
    Member();

    Member(string username, string password, string fullName, string phone);

    static Member *login(); // done

    void addHouse(); // done

    bool listHouse(); // done

    bool unlistHouse(); // done

    void sendRequest(int num); // done

    bool viewRequest();

    bool acceptRequest(int num);

    void cancelRequest();

    void viewMemberReviews(int num);

    Member *rateMember(int num);

    House *rateHouse();

    // ----------------------------------------NU------------------------------------- //

    template <class T>
    void rate(T *object);

    // void rate(Member *member);

    // void rate(House *house);

    // Check the houses matched with date, city, rating and credit of user
    // then add all of them to availableHouses attribute
    bool checkAvailableHouses(); // done

    // Display review of selected house in the availableHouses attribute
    void viewReviews(int num); // done

    friend class House;
    friend class Rating;
    friend class Request;
    friend class DataHandler;
    friend class User;
};