#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using namespace std;

bool checkBlankAndSpaces(string input);
class User{
    private:
        string username;
        string fullName; 
        string phoneNumber;
        string creditPoints = "500";
        string location = "";
        string description;
        string password;
    public:
        void Register();
        void viewHouse();
};
