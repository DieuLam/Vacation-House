#include <iostream>
#include <vector>
using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

class Member;
class House;
class Rating;
class Request;

class DataHandler {
    static vector<Member *> memberList;

    DataHandler();

    void addMember(Member *member); 

    friend class Member;
    friend class House;
    friend class Rating;
    friend class Request;
};

