#include "User.h"

bool checkBlankAndSpaces(string input){ //check if input contains white spaces or its blank
    int errorsCount = 0;
    if(input.compare("") == 0){
        cout<<"Cannot be blanked\n";
        return false;
    }
    for (int i=0; i<input.length(); i++){ //check if there's space in input
        if (isspace(input[i]))
            errorsCount = errorsCount + 1;
    }
    if(errorsCount != 0){
        cout<<"There cannot be white spaces in your input\n";
        return false;
    }
    return true;
};

void User::Register(){
    fstream registrationFile;
    fstream houseInfoFile;
    string lineToSave;
    cout<<"Welcome, you can now register your account\n";
    cout<<"Initial entry fee will be $500\n";
    cout<<"You will earn 500 credit points after you have successfully create your account\n";
    bool validInput = false;
    while(validInput != true){
        int countErrors = 0;
        cout<<"Please enter your username(with no whitespaces): ";
        getline(cin,username);
        validInput = checkBlankAndSpaces(username); //if false, it means there are white spaces or blanked input
        if(validInput == 0) //means validInput = false
            continue; //skip the current loop so dont have to waste time check with file

        // registrationFile.open("registrationInfo.txt",ios::in); //ios::in to open file performing read operations
        // string temp;
        // string delimeter = "|";
        // while(getline(registrationFile,temp)){//save line to string temp
        //     size_t pos = 0; //pos = positions
        //     string savedUsername;
        //     pos = temp.find(delimeter); //find position of first delimeter
        //     savedUsername = temp.substr(0,pos); //get the string from position 0 to position of first delimeter
        //     if(username.compare(savedUsername)== 0){ //if username in the line equals input
        //         cout<<"Your entered username has already been used \n";
        //         countErrors = countErrors + 1;
        //     }
        // }

        
        if (countErrors != 0){
            validInput = false;
            cout<<"Your input is invalid\n";
        }else{
            validInput = true;
        }
        registrationFile.close();
    }
    cout<<"Please enter your full name: "; 
    getline(cin,fullName);

    validInput = false; //set validInput back to false for next while loop
    while(validInput != true){
        cout<<"Please enter your password: "; 
        getline(cin,password);
        validInput = checkBlankAndSpaces(password);
        if(validInput == 0) //means validInput = false
            continue;
    }

    validInput = false; //set it back to false for the next while loop
    while (validInput != true){
        cout<<"Please enter a valid phone number with no white spaces in between: ";
        getline(cin,phoneNumber);
        int nonIntegerCount = 0;
        for (int i = 0; i < phoneNumber.length(); i++){
            if (isdigit(phoneNumber[i]) == false){ // if char[i] is not a digit
                nonIntegerCount = nonIntegerCount + 1;
            }
        }
        if(nonIntegerCount != 0){
            cout<<"Invalid input, try again\n";
            validInput = false;
        }else{
            validInput = true;
        }
    }
    string decision;
    validInput = false; //set back to false for next while loop
    cout<<"Do you want to enter information about your house(optional) if available?\n";
    while (validInput != true){
        cout<<"Type 'y' if you want to enter and 'n' if you don't want to: ";
        getline(cin,decision);
        if(decision.compare("y") == 0){ //if user chose yes
            cout<<"Please enter your house location: ";
            getline(cin,location);//so we can read white spaces between words
            cout<<"Please enter your house description below:\n";
            getline(cin,description);//so we can read white spaces between words

            //save to houseInfo file
            houseInfoFile.open("houseInfo.txt",ios::app); //ios::app to append a new line to the file
            lineToSave = username +"|"+ phoneNumber +"|" + location + "|" + description; // use | because when enter location, user might use / or \ or ,
            houseInfoFile<<"\n"<<lineToSave;
            houseInfoFile.close();
            validInput = true;
        }
        else if(decision.compare("n") == 0){ //if user choose no;
            cout<<"You can add your house for exchange anytime you wish after you logged in with your account\n";
            validInput = true;
        }
        else{
            cout<<"Please enter a valid input"<<endl;
            validInput = false;
        }
    }
    //record registration data in registration.txt file;
    registrationFile.open("registrationInfo.txt",ios::app); //ios::app to append a new line to the file
    lineToSave = username + "|" + fullName + "|" + password + "|" + phoneNumber + "|" + creditPoints; 
    registrationFile<<"\n"<<lineToSave;
    registrationFile.close();
    cout<<"Your registration has been complete, you can now log in\n";
    
};
void User::viewHouse(){
    fstream houseInfoFile;
    cout<<"Since you have't logged in, you can only view house details: \n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    houseInfoFile.open("houseInfo.txt",ios::in); //ios::in to open file performing read operations
    string temp;
    string delimeter = "|";
    while(getline(houseInfoFile,temp)){//save line to string temp
        size_t pos = 0;
        string subString;
        vector<string> printInfo; //save each element into a vector
        while ((pos = temp.find (delimeter)) != std::string::npos){ //use find() here to get position of delimiters
            subString = temp.substr(0,pos); //subString is equals to all string up to delimiter '|'
            printInfo.push_back(subString); //put the subString into the vector
            temp.erase(0,pos + delimeter.length()); //delete the subString from the line so the next subString won't be repeated
        }
        printInfo.push_back(temp); //since temp should now only have the last element, push it 

        //print information
        cout<<"Owner Username: "<<printInfo[0]<<"\n";
        cout<<"Owner phone number: "<<printInfo[1]<<"\n";
        cout<<"Owner House location: "<<printInfo[2]<<"\n";
        cout<<"Owner House descriptions: "<<printInfo[3]<<"\n";
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    }
    houseInfoFile.close();
};
// int main(){ //main method is for testing, remove this once program complete
//     User user;
//     user.Register();
//     //user.viewHouse();
//     return 0;
// }
