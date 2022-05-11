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
    double consummingCredits, minOccRating;
    Member *owner;
    vector<Member *> occupierList;
    vector<Rating *> ratings;
    vector<Request *> requestList;

public:
    House();

    House(Member *owner, string city, string description);

    void setData(string startDate, string endDate, int minRating, double conCredits);

    void resetDate(string date);

    void addOccupier(Member *member);

    void addRequest(Member *member, string start, string end);
    friend class Member;
    friend class Rating;
    friend class Request;
    friend class DataHandler;
};