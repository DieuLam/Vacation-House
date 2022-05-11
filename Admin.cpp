#include "Admin.h"

bool Admin::login(string inputUsername, string inputPass){
    int errors = 0;
    if(inputUsername.compare(username) == 0 ){ //if same username
        if(inputPass.compare(password) == 0){ //if same password
            cout<<"Admin account has been succesfully logged in \n";
            //return true;
        }else{
            cout<<"Incorrect password or password\n";
            errors = errors + 1;
        }
    }else{
        cout<<"Incorrect username or password\n";
        errors = errors + 1;
    }
    if(errors != 0){
        return false;
    }
    return true;
};
void Admin::viewMember(){
    fstream registrationFile;
    cout<<"Below is all Member information\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    registrationFile.open("registrationInfo.txt",ios::in); //ios::in to open file performing read operations
    string temp;
    string delimeter = "|";
    while(getline(registrationFile,temp)){//save line to string temp
        size_t pos = 0;
        string subString;
        if(!temp.empty()){
            vector<string> printInfo; //save each element into a vector
            while ((pos = temp.find (delimeter)) != std::string::npos){ //use find() here to get position of delimiters
                subString = temp.substr(0,pos); //subString is equals to all string up to delimiter '|'
                printInfo.push_back(subString); //put the subString into the vector
                temp.erase(0,pos + delimeter.length()); //delete the subString from the line so the next subString won't be repeated
            }
            printInfo.push_back(temp);

            //Print statement for each line in file
            cout<<"Username: "<<printInfo[0]<<"\n";
            cout<<"User's full name: "<<printInfo[1]<<"\n";
            cout<<"User's password: "<<printInfo[2]<<"\n";
            cout<<"User's phone number: "<<printInfo[3]<<"\n";
            cout<<"User's credit points: "<<printInfo[4]<<"\n";
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
        }
    }
    registrationFile.close();
};
void Admin::viewHouse(){
    fstream houseInfoFile;
    cout<<"Below is all House information for all member\n";
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
