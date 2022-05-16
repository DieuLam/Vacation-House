#include "Admin.h"
#include "Member.h"
#include "House.h"
#include "DataHandler.h"

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
        cout << "Incorrect username or password\n";
        errors = errors + 1;
    }
    if (errors != 0)
    {
        return false;
    }
    return true;
};

void Admin::viewMember()
{
    if (DataHandler::memberList.size() > 0)
    {

        cout << "\nBelow is all Member information\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";

        for (int i = 0; i < DataHandler::memberList.size(); i++)
        {
            cout << i << ") ";
            DataHandler::memberList.at(i)->showMemberInfo();
        }

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    }

    cerr << "\nNo member to display\n";
};

void Admin::viewHouse()
{
    if (DataHandler::memberList.size() > 0)
    {
        cout << "Below is all House information for all member\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
        for (int i = 0; i < DataHandler::memberList.size(); i++)
        {
            cout << i << ") ";
            DataHandler::memberList.at(i)->showHouseInfo();
        }
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    }

    cerr << "\nNo house to display\n";
};
