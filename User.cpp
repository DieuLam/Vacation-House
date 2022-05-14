#include "User.h"
#include "Member.h"
#include "DataHandler.h"

bool checkBlankAndSpaces(string input)
{ // check if input contains white spaces or its blank
    int errorsCount = 0;
    if (input.compare("") == 0)
    {
        cout << "Cannot be blanked\n";
        return false;
    }
    for (int i = 0; i < input.length(); i++)
    { // check if there's space in input
        if (isspace(input[i]))
            errorsCount = errorsCount + 1;
    }
    if (errorsCount != 0)
    {
        cout << "There cannot be white spaces in your input\n";
        return false;
    }
    return true;
};

void User::Register()
{
    string username;
    string fullName;
    string phoneNumber;
    string password;

    cout << "Welcome, you can now register your account\n";
    cout << "Initial entry fee will be $500\n";
    cout << "You will earn 500 credit points after you have successfully create your account\n";

    bool validInput = false;
    while (validInput != true)
    {
        int countErrors = 0;
        cout << "Please enter your username(with no whitespaces): ";
        getline(cin, username);
        validInput = checkBlankAndSpaces(username); // if false, it means there are white spaces or blanked input
        if (validInput == 0)                        // means validInput = false
            continue;                               // skip the current loop so dont have to waste time check with file

        if (countErrors != 0)
        {
            validInput = false;
            cout << "Your input is invalid\n";
        }
        else
        {
            validInput = true;
        }
    }
    cout << "Please enter your full name: ";
    getline(cin, fullName);

    validInput = false; // set validInput back to false for next while loop
    while (validInput != true)
    {
        cout << "Please enter your password: ";
        getline(cin, password);
        validInput = checkBlankAndSpaces(password);
        if (validInput == 0) // means validInput = false
            continue;
    }

    validInput = false; // set it back to false for the next while loop
    while (validInput != true)
    {
        cout << "Please enter a valid phone number with no white spaces in between: ";
        getline(cin, phoneNumber);
        int nonIntegerCount = 0;
        for (int i = 0; i < phoneNumber.length(); i++)
        {
            if (isdigit(phoneNumber[i]) == false)
            { // if char[i] is not a digit
                nonIntegerCount = nonIntegerCount + 1;
            }
        }
        if (nonIntegerCount != 0)
        {
            cout << "Invalid input, try again\n";
            validInput = false;
        }
        else
        {
            validInput = true;
        }
    }

    DataHandler::addMember(new Member(username, password, fullName, phoneNumber));

    string decision;
    validInput = false; // set back to false for next while loop
    cout << "Do you want to enter information about your house(optional) if available?\n";
    while (validInput != true)
    {
        cout << "Type 'y' if you want to enter and 'n' if you don't want to: ";
        getline(cin, decision);
        if (decision.compare("y") == 0)
        { // if user chose yes
            DataHandler::memberList.back()->addHouse();
            validInput = true;
        }
        else if (decision.compare("n") == 0)
        { // if user choose no;
            cout << "You can add your house for exchange anytime you wish after you logged in with your account\n";
            validInput = true;
        }
        else
        {
            cout << "Please enter a valid input" << endl;
            validInput = false;
        }
    }

    cout << "Your registration has been completed. You can now login as a Member\n";
};
void User::viewHouse()
{
    fstream houseInfoFile;
    cout << "Since you have't logged in, you can only view house details: \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
};
// int main(){ //main method is for testing, remove this once program complete
//     User user;
//     user.Register();
//     //user.viewHouse();
//     return 0;
// }
