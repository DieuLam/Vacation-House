#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

class Request;
class Member;
class Rating;

class House
{
private:
    string city, description, startDate, endDate;
    double minOccRating;
    int consummingCredits;
    Member *owner ;
    vector<Member *> occupierList;
    vector<Rating *> ratings;
    vector<Request *> requestList;

public:
    House();

    House(Member *owner, string city, string description, string start, string end, double min, int credit);

    void showOccupierList();

    void showInfo();

    void setData(string startDate, string endDate, double minRating, double conCredits);

    void resetDate(string date);

    void addOccupier(Member *member);

    void addRequest(Member *member, string start, string end, int numDay);
    
    friend class Member;
    friend class Rating;
    friend class Request;
    friend class DataHandler;
};