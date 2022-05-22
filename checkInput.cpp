#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using std::cin;
using std::cout;
using std::string;

// check credit only number
bool checknum(string input)
{
    if (input.compare("") == 0)
    {
        cout << "Cannot be blanked\n";
        return false;
    }
    int errorsCount = 0;
    if (input[0] == '-')
    {
        for (int i = 1; i < input.length(); i++)
        {
            if (isdigit(input[i]) == false)
            {
                errorsCount = errorsCount + 1;
            }
        }
    }
    else
    {
        for (int i = 1; i < input.length(); i++)
        {
            {
                if (isdigit(input[i]) == false)
                {
                    errorsCount = errorsCount + 1;
                }
            }
        }
    }

    if (errorsCount != 0)
    {
        cout << "Invalid input\n";
        return false;
    }
    return true;
};

// check rating -10 to 10
bool checkRating(string input)
{
    if (input.compare("") == 0)
    {
        cout << "Cannot be blanked\n";
        return false;
    }
    bool r = checknum(input);
    if (r != true)
    {
        return false;
    }
    else
    {
        int s = std::stoi(input);
        if (-10 > s || s > 10)
        {
            return false;
        }
    }
    return true;
};

// check city
bool checkCity(string input)
{
    string Arr[3] = {"Saigon", "Hanoi", "Da Nang"};
    if (input.compare("") == 0)
    {
        cout << "\nCannot be blanked\n";
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        if (input.compare(Arr[i]) == 0)
        {
            return true;
        }
    }

    cout << "\nThe city must be in the list\n";
    return false;
}


int changeToInt(string input) {
    int x = stod(input);

    cout << x;
    return x;
}

// int main() {
//    string str = "-10";

//    changeToInt(str);
// }