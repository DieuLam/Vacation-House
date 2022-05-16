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
    double credit = 500.0;
    int numDays;
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

    bool viewRequest(); // done

    bool acceptRequest(int num); // done

    void cancelRequest(); // done

    void viewMemberReviews(int num); // done

    void rateMember(); // done

    void rateHouse(); // done

    void showMemberInfo(); //done

    void showHouseInfo(); //done

    void showRequestList();

    // ----------------------------------------NU------------------------------------- //

    template <class T>
    void rate(T *object);
    bool checkAvailableHouses(); // done
    void viewReviews(int num);   // done

    friend class House;
    friend class Rating;
    friend class Request;
    friend class DataHandler;
    friend class User;
};