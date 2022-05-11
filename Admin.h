#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Admin{
    private:
        string username = "admin";
        string password = "password";
    public:
        bool login(string inputUsername, string inputPass);
        void viewMember();
        void viewHouse();
};
