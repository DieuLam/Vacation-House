#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Admin
{
private:
    string username = "admin";
    string password = "password";

public:
    bool login(string inputUsername, string inputPass);
    void viewMember();
    void viewHouse();

    friend class DataHandler;
};
