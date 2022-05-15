#include <iostream>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

class Member;
class House;
// class DataHandler;

class Request
{
private:
    Member *sender;
    House *house;
    string startDate;
    string endDate;

public:
    Request();

    Request(Member *sender, House *house, string start, string end);

    friend class Member;
    friend class House;
    // friend class DataHandler;
};