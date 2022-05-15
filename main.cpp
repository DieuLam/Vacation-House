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
    cout << "\nEEET2482/COSC2082 ASSIGNMENT VACATION HOUSE EXCHANGE APPLICATION\n";
    cout << "Instructor: Mr. Linh Tran\n";
    cout << "Group: Group 14\n";
    cout << "s39116151, Cao Ngoc Son\n";
    cout << "s3878058, Nguyen Hai Minh Trang\n";
    cout << "s3877961, Le Ngoc Nguyen Thuan\n";
    cout << "s3877664, Lam Tin Dieu\n";

    int exitStatus = 0; // if exitStatus = 1, means exit
    while (exitStatus == 0)
    {
        cout << "\nUse the app as: 1.Guest      2.Member        3.Admin         4.EXIT\n";
        string appChoices;
        cout << "Enter your choice (1-4): ";
        getline(cin, appChoices);

        if (appChoices.compare("1") == 0)
        { // if user select guest;
            User user;
            int guestExit = 0;
            while (guestExit != 1)
            { // 3 stands for exit
                cout << "\nSelect guest actions:      1. Register       2. View Houses information     3. Exit to main menu\n";
                string guestOptions;
                cout << "Enter your choice (1-3): ";
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
                    cout << "\nExit to main menu\n";
                    guestExit = 1;
                }
                else
                {
                    cout << "\nPlease enter a valid input\n";
                }
            }
        }
        else if (appChoices.compare("2") == 0)
        { // if select member
            cout << "\nPlease login to continue\n";
            Member *login = Member::login();
            bool exitMember = false;
            if (login != NULL)
            {
                while (exitMember == false)
                {
                    string option;
                    cout << "\nSelect Member actions:\n";
                    cout << "1. Add House\n";
                    cout << "2. List/Unlist House\n";
                    cout << "3. View House's occupying requests\n";
                    cout << "4. View available houses for rent\n";
                    cout << "5. View current profile\n";
                    cout << "6. Rate House/Occupiers\n";
                    cout << "7. Exit to main menu\n";
                    cout << "Enter your choice (1-7): ";
                    getline(cin, option);

                    if (option.compare("1") == 0)
                    {
                        login->addHouse();
                    }

                    else if (option.compare("2") == 0)
                    {
                        bool exitListHouse = false;
                        while (!exitListHouse)
                        {
                            cout << "\nPlease select an option\n";
                            cout << "1. List House\n";
                            cout << "2. Unlist House\n";
                            cout << "3. Back to previous menu\n";
                            cout << "Enter your choice (1-3): ";
                            getline(cin, option);
                            if (option.compare("1") == 0)
                            {
                                login->listHouse();
                            }
                            else if (option.compare("2") == 0)
                            {
                                login->unlistHouse();
                            }
                            else if (option.compare("3") == 0)
                            {
                                exitListHouse = true;
                            }
                            else
                            {
                                cout << "\nPlease enter a valid input\n";
                            }
                        }
                    }

                    else if (option.compare("3") == 0)
                    {
                        bool exitHouseRequest = false;
                        if (login->viewRequest())
                        {
                            while (!exitHouseRequest)
                            {
                                cout << "\nPlease select an option: \n";
                                cout << "1. Accept a request\n";
                                cout << "2. View detailed reviews of a sender\n";
                                cout << "3. Back to previous menu\n";
                                cout << "Enter your choice: ";
                                getline(cin, option);

                                if (option.compare("1") == 0)
                                {
                                    cout << "\nPlease choose a house by entering a number: \n";
                                    getline(cin, option);
                                    login->acceptRequest(stoi(option) - 1);
                                }

                                else if (option.compare("2") == 0)
                                {
                                    cout << "\nPlease choose a house by entering a number: \n";
                                    getline(cin, option);
                                    login->viewMemberReviews(stoi(option) - 1);
                                }

                                else if (option.compare("3") == 0)
                                {
                                    cout << "\nBack to previous menu\n";
                                    exitHouseRequest = true;
                                }

                                else
                                {
                                    cout << "\nPlease enter a valid input\n";
                                }
                            }
                        };
                    }

                    else if (option.compare("4") == 0)
                    {
                        bool exitAvailableHouse = false;
                        if (login->checkAvailableHouses())
                        {
                            while (!exitAvailableHouse)
                            {
                                cout << "\nPlease choose an option: \n";
                                cout << "1. View detailed reviews of a house \n";
                                cout << "2. Request to rent a house \n";
                                cout << "3. Back to previous menu \n";
                                cout << "Enter your choice (1-3): ";
                                getline(cin, option);

                                if (option.compare("1") == 0)
                                {
                                    cout << "\nPlease choose a house by entering a number: \n";
                                    getline(cin, option);
                                    login->viewReviews(stoi(option) - 1);
                                }

                                else if (option.compare("2") == 0)
                                {
                                    login->checkAvailableHouses();
                                    cout << "\nPlease choose a house by entering a number: \n";
                                    getline(cin, option);
                                    login->sendRequest(stoi(option) - 1);
                                }

                                else if (option.compare("3") == 0)
                                {
                                    cout << "\nBack to previous menu\n\n";
                                    exitAvailableHouse = true;
                                }
                                else
                                {
                                    cerr << "\nPlease enter a valid input (1->3)\n";
                                }
                            }
                        };
                    }

                    else if (option.compare("5") == 0)
                    {
                        bool exitViewProfile = false;
                        while (!exitViewProfile)
                        {

                            cout << "\nPlease select an option:\n";
                            cout << "1. View your profile\n";
                            cout << "2. View house profile\n";
                            cout << "3. View requests sent\n";
                            cout << "4. Back to previous menu\n";
                            cout << "Enter your choice (1-4): ";
                            getline(cin, option);

                            if (option.compare("1") == 0)
                            {
                                login->showMemberInfo();
                            }
                            else if (option.compare("2") == 0)
                            {
                                login->showHouseInfo();
                            }
                            else if (option.compare("3") == 0)
                            {
                                
                            }
                            else if (option.compare("4") == 0)
                            {
                                cout << "\nBack to previous menu\n";
                                exitViewProfile = true;
                            }
                        }
                    }

                    else if (option.compare("6") == 0)
                    {
                        bool exitRate = false;
                        while (!exitRate)
                        {
                            cout << "\nPlease select an option: \n";
                            cout << "1. Rate house\n";
                            cout << "2. Rate occupiers\n";
                            cout << "3. Back to previous menu\n";
                            cout << "Enter your choice: ";
                            getline(cin, option);

                            if (option.compare("1") == 0)
                            {
                                login->rateHouse();
                            }

                            else if (option.compare("2") == 0)
                            {
                                // Check if occupier list is not empty
                                login->rateMember();
                            }

                            else if (option.compare("3") == 0)
                            {
                                cout << "\nBack to previous menu\n";
                                exitRate = true;
                            }

                            else
                            {
                                cerr << "\nPlease enter a valid input (1/2/3)\n";
                            }
                        }
                    }

                    else if (option.compare("7") == 0)
                    {
                        exitMember = true;
                    }
                }
            }
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
                    cout << "\nSelect admin actions:      1. View all member information       2. View all Houses information     3. Exit to main menu\n";
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
                        cout << "\nExit to main menu\n";
                        adminExit = 1;
                    }
                    else
                    {
                        cout << "\nPlease enter a valid input\n";
                    }
                }
            }
        }
        else if (appChoices.compare("4") == 0)
        { // if exit
            cout << "\nThank you for using the app \n";
            exitStatus = 1;
        }
        else
        { // invalid input
            cout << "\nPlease enter a valid input(1,2,3 or 4)\n";
        }
    }

    return 0;
}
