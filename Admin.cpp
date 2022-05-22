#include "header_files/Admin.h"
#include "header_files/Member.h"
#include "header_files/House.h"
#include "header_files/DataHandler.h"

bool Admin::login(string inputUsername, string inputPass)
{
    int errors = 0;
    if (inputUsername.compare(username) == 0)
    { // if same username
        if (inputPass.compare(password) == 0)
        { // if same password
            cout << "\nAdmin account has been succesfully logged in \n";
            // return true;
        }
        else
        {
            cout << "\nIncorrect password or password\n";
            errors = errors + 1;
        }
    }
    else
    {
        cout << "\nIncorrect username or password\n";
        errors = errors + 1;
    }
    if (errors != 0)
    {
        return false;
    }
    return true;
};

// display all members in the system
void Admin::viewMember()
{
    if (DataHandler::memberList.size() > 0)
    {

        cout << "\nBelow is all Member information\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";

        for (int i = 0; i < DataHandler::memberList.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ") ";
            DataHandler::memberList.at(i)->showMemberInfo();
        }

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    }
    else
    {

        cerr << "\nNo member to display\n";
    }
};

// display all houses in the system
void Admin::viewHouse()
{
    if (DataHandler::memberList.size() > 0)
    {
        cout << "\nBelow is all House information for all member\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
        for (int i = 0; i < DataHandler::houseInfoList.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ") ";
            DataHandler::houseInfoList.at(i)->owner->showHouseInfo();
        }
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    }
    else
    {
        cerr << "\nNo house to display\n";
    }
};
