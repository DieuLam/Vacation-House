#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Member;
class DataHandler;

bool checkBlankAndSpaces(string input);
class User
{
public:
    void Register();
    void viewHouse();

    friend class Member;
    friend class DataHandler;
};
