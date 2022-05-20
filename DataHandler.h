#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::fstream;
using std::ios;
using namespace std;
class Member;
class House;
class Rating;
class Request;

class DataHandler {
    private:
    static vector<Member *> memberList;
    static vector<House *> houseInfoList;

    static void addMember(Member *member); 
    static void addHouse(House *house);


    friend class Member;
    friend class House;
    friend class Rating;
    friend class Request;
    friend class User;
    friend class Admin;
    

    public:

    DataHandler();
    static void saveVectorsToFile();
    static void loadFilesToVector(string path, int whichFiles);
    friend class main;


};

