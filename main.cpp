#include <iostream>
#include "Admin.h"
#include "User.h"
#include "Member.h"
#include "House.h"
#include "Rating.h"
#include "Request.h"
using namespace std;

int main()
{
    cout << "EEET2482/COSC2082 ASSIGNMENT VACATION HOUSE EXCHANGE APPLICATION\n";
    cout << "Instructor: Mr. Linh Tran\n";
    cout << "Group: Group 14\n";
    cout << "s39116151, Cao Ngoc Son\n";
    cout << "s3878058, Nguyen Hai Minh Trang\n";
    cout << "s3877961, Le Ngoc Nguyen Thuan\n";
    cout << "s3877664, Lam Tin Dieu\n";

    int exitStatus = 0; // if exitStatus = 1, means exit
    while (exitStatus == 0)
    {
        cout << "Use the app as: 1.Guest      2.Member        3.Admin         4.EXIT\n";
        string appChoices;
        cout << "Enter your choice(1-4): ";
        getline(cin, appChoices);

        if (appChoices.compare("1") == 0)
        { // if user select guest;
            User user;
            int guestExit = 0;
            while (guestExit != 1)
            { // 3 stands for exit
                cout << "Select guest actions:      1.Register       2.view Houses information     3.Exit to main menu\n";
                string guestOptions;
                cout << "Enter your choice: ";
                getline(cin, guestOptions);
                if (guestOptions.compare("1") == 0)
                { // view member list
                    user.Register();
                }
                else if (guestOptions.compare("2") == 0)
                {
                    user.viewHouse();
                }
                else if (guestOptions.compare("3") == 0)
                {
                    cout << "Exit to main menu\n";
                    guestExit = 1;
                }
                else
                {
                    cout << "Please enter a valid input\n";
                }
            }
        }
        else if (appChoices.compare("2") == 0)
        { // if select member
            cout << "Please login to continue\n";
            Member::login();
            cout << "Select Member actions:\n";
            cout << "1. Add/Edit/View House\n";
            cout << "2. View available houses for rent\n";
            cout << "2. View current profile\n";
            cout << "2. Exit\n";
        }
        else if (appChoices.compare("3") == 0)
        { // if select admin
            string inputUsername;
            cout << "Enter admin username: ";
            getline(cin, inputUsername);
            string inputPass;
            cout << "Enter admin password: ";
            getline(cin, inputPass);
            Admin admin;
            bool loginStatus = admin.login(inputUsername, inputPass);
            if (loginStatus == true)
            { // if logged in
                int adminExit = 0;
                while (adminExit != 1)
                { // 3 stands for exit
                    cout << "Select admin actions:      1.view all member information       2.view all Houses information     3.Exit to main menu\n";
                    string adminOptions;
                    cout << "Enter your choice: ";
                    getline(cin, adminOptions);
                    if (adminOptions.compare("1") == 0)
                    { // view member list
                        admin.viewMember();
                    }
                    else if (adminOptions.compare("2") == 0)
                    { // view house list
                        admin.viewHouse();
                    }
                    else if (adminOptions.compare("3") == 0)
                    {
                        cout << "Exit to main menu\n";
                        adminExit = 1;
                    }
                    else
                    {
                        cout << "Please enter a valid input\n";
                    }
                }
            }
        }
        else if (appChoices.compare("4") == 0)
        { // if exit
            cout << "Thank you for using the app \n";
            exitStatus = 1;
        }
        else
        { // invalid input
            cout << "Please enter a valid input(1,2,3 or 4)\n";
        }
    }

    return 0;
}
