#include <iostream>
#include "header_files/Admin.h"
#include "header_files/User.h"
#include "header_files/Member.h"
#include "header_files/House.h"
#include "header_files/Rating.h"
#include "header_files/Request.h"
#include "header_files/DataHandler.h"
using namespace std;

int main()
{
    cout << "\nEEET2482/COSC2082 ASSIGNMENT VACATION HOUSE EXCHANGE APPLICATION\n";
    cout << "Instructor: Mr. Linh Tran\n";
    cout << "Group: 14\n";
    cout << "s3916151, Cao Ngoc Son\n";
    cout << "s3878058, Nguyen Hai Minh Trang\n";
    cout << "s3877961, Le Ngoc Nguyen Thuan\n";
    cout << "s3877664, Lam Tin Dieu\n";

    DataHandler data;

    data.loadFilesToVector("files_database/registrationInfo.txt", 1); // load all files to corresponding vectors
    data.loadFilesToVector("files_database/houseInfo.txt", 2);        // the second parameter decides which file to load into
    data.loadFilesToVector("files_database/houseRating.txt", 3);
    data.loadFilesToVector("files_database/memberRating.txt", 4);
    data.loadFilesToVector("files_database/registrationInfo.txt", 5);
    data.loadFilesToVector("files_database/request.txt", 6);

    int exitStatus = 0; // if exitStatus = 1, means exit

    while (exitStatus == 0)
    {
        cout << "\nUse the app as: 1.Guest      2.Member        3.Admin         4.EXIT\n";
        string appChoices;
        cout << "Enter your choice (1-4): ";
        getline(cin, appChoices);

        if (appChoices.compare("1") == 0) // if user select guest
        {
            User user;
            int guestExit = 0;
            while (guestExit != 1)
            {
                cout << "\nSelect guest actions:      1. Register       2. View Houses information     3. Exit to main menu\n";
                string guestOptions;
                cout << "Enter your choice (1-3): ";
                getline(cin, guestOptions);
                if (guestOptions.compare("1") == 0) // register
                {
                    user.Register();
                }
                else if (guestOptions.compare("2") == 0) // view house info
                {
                    user.viewHouse();
                }
                else if (guestOptions.compare("3") == 0) // exit guest
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

        else if (appChoices.compare("2") == 0) // if user select member
        {
            cout << "\nPlease login to continue\n";
            Member *login = Member::login();
            bool exitMember = false;

            if (login != NULL) // if log in successfully
            {
                while (exitMember == false) // display the menu when user not select exit
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

                    if (option.compare("1") == 0) // add house
                    {
                        login->addHouse();
                    }

                    else if (option.compare("2") == 0) // list/unlist house
                    {
                        bool exitListHouse = false;
                        while (!exitListHouse) // display the below menu until user select 3
                        {
                            cout << "\nPlease select an option\n";
                            cout << "1. List House\n";
                            cout << "2. Unlist House\n";
                            cout << "3. Back to previous menu\n";
                            cout << "Enter your choice (1-3): ";
                            getline(cin, option);

                            if (option.compare("1") == 0) // list house
                            {
                                login->listHouse();
                            }
                            else if (option.compare("2") == 0) // unlist house
                            {
                                login->unlistHouse();
                            }
                            else if (option.compare("3") == 0) // back
                            {
                                exitListHouse = true;
                            }
                            else
                            {
                                cout << "\nPlease enter a valid input\n";
                            }
                        }
                    }

                    else if (option.compare("3") == 0) // view occupying requests of the house
                    {
                        bool exitHouseRequest = false;
                        if (login->viewRequest()) // display all requests sent to member's house
                        {
                            while (!exitHouseRequest) // display the menu until user select 3
                            {
                                cout << "\nPlease select an option: \n";
                                cout << "1. Accept a request\n";
                                cout << "2. View detailed reviews of a sender\n";
                                cout << "3. Back to previous menu\n";
                                cout << "Enter your choice: ";
                                getline(cin, option);

                                if (option.compare("1") == 0) // accept request
                                {
                                    if (login->viewRequest())
                                    {
                                        cout << "\nPlease choose a request by entering a number: ";
                                        getline(cin, option);
                                        if (isdigit(option[0])) // check user input
                                        {
                                            login->acceptRequest(stoi(option) - 1); // -1 to get the correct index in the vector
                                        }
                                        else
                                        {
                                            cout << "\nInvalid input\n";
                                        }
                                    }
                                }
                                else if (option.compare("2") == 0) // view review of requesters
                                {
                                    if (login->viewRequest())
                                    {
                                        cout << "\nPlease choose a sender by entering a number: ";
                                        getline(cin, option);
                                        if (isdigit(option[0])) // check user input
                                        {
                                            login->viewMemberReviews(stoi(option) - 1); // -1 to get the correct index in the vector
                                        }
                                        else
                                        {
                                            cout << "\nInvalid input\n";
                                        }
                                    }
                                }
                                else if (option.compare("3") == 0) // back
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

                    else if (option.compare("4") == 0) // view available house
                    {
                        bool exitAvailableHouse = false;
                        if (login->checkAvailableHouses()) // display all available house to rent
                        {
                            while (!exitAvailableHouse) // display this menu until user select 3
                            {
                                cout << "\nPlease choose an option: \n";
                                cout << "1. View detailed reviews of a house \n";
                                cout << "2. Request to rent a house \n";
                                cout << "3. Back to previous menu \n";
                                cout << "Enter your choice (1-3): ";
                                getline(cin, option);

                                if (option.compare("1") == 0) // view review of the house
                                {
                                    cout << "\nPlease choose a house by entering a number: ";
                                    getline(cin, option);
                                    if (isdigit(option[0])) // check user input
                                    {
                                        login->viewHouseReviews(stoi(option) - 1); // -1 to get the correct index in the vector
                                    }
                                    else
                                    {
                                        cout << "\nInvalid input\n";
                                    }
                                }

                                else if (option.compare("2") == 0)
                                {
                                    cout << "\nPlease choose a house by entering a number: ";
                                    getline(cin, option);
                                    if (isdigit(option[0])) // check user input
                                    {
                                        login->sendRequest(stoi(option) - 1); // -1 to get the correct index in the vector
                                    }
                                    else
                                    {
                                        cout << "\nInvalid input\n";
                                    }
                                }

                                else if (option.compare("3") == 0) // back
                                {
                                    cout << "\nBack to previous menu\n";
                                    exitAvailableHouse = true;
                                }
                                else
                                {
                                    cerr << "\nPlease enter a valid input\n";
                                }
                            }
                        };
                    }

                    else if (option.compare("5") == 0) // view self and house's profile
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

                            if (option.compare("1") == 0) // all info of this member
                            {
                                login->showMemberInfo();
                            }
                            else if (option.compare("2") == 0) // all info of this member's house
                            {
                                login->showHouseInfo();
                            }
                            else if (option.compare("3") == 0) // all requests this member have sent
                            {
                                login->showRequestList();
                            }
                            else if (option.compare("4") == 0) // back
                            {
                                cout << "\nBack to previous menu\n";
                                exitViewProfile = true;
                            }
                            else
                            {
                                cerr << "\nPlease enter a valid input\n";
                            }
                        }
                    }

                    else if (option.compare("6") == 0) // rate
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

                            if (option.compare("1") == 0) // rate house this member has occupied
                            {
                                login->rateHouse();
                            }
                            else if (option.compare("2") == 0) // rate occupiers of this member's house
                            {
                                login->rateMember();
                            }
                            else if (option.compare("3") == 0) // back
                            {
                                cout << "\nBack to previous menu\n";
                                exitRate = true;
                            }

                            else
                            {
                                cerr << "\nPlease enter a valid input\n";
                            }
                        }
                    }

                    else if (option.compare("7") == 0) // exit member menu
                    {
                        exitMember = true;
                    }

                    else
                    {
                        cerr << "\nPlease enter a valid input\n";
                    }
                }
            }
        }

        else if (appChoices.compare("3") == 0) // if select admin
        {
            string inputUsername;
            cout << "\nEnter admin username: ";
            getline(cin, inputUsername);
            string inputPass;
            cout << "Enter admin password: ";
            getline(cin, inputPass);

            Admin admin;
            bool loginStatus = admin.login(inputUsername, inputPass);

            if (loginStatus == true) // if logged in
            { 
                int adminExit = 0;
                while (adminExit != 1)
                { 
                    cout << "\nSelect admin actions:      1. View all Member information       2. View all Houses information     3. Exit to main menu\n";
                    string adminOptions;
                    cout << "Enter your choice: ";
                    getline(cin, adminOptions);

                    if (adminOptions.compare("1") == 0) // view member list
                    { 
                        admin.viewMember();
                    }
                    else if (adminOptions.compare("2") == 0) // view house list
                    { 
                        admin.viewHouse();
                    }
                    else if (adminOptions.compare("3") == 0) // exit admin
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

        else if (appChoices.compare("4") == 0) // if exit
        { 
            cout << "\nThank you for using the app \n";

            data.saveVectorsToFile(); // from class datahandler

            exitStatus = 1;
        }
        else // invalid app choice input
        { 
            cout << "\nPlease enter a valid input(1,2,3 or 4)\n";
        }
    }
    return 0;
}
