#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using std::string;
using namespace std;

class User{
    private:
    string username;
    string fullName;
    string phoneNumber;
    string creditPoints = "500";
    string location = "";
    string description;
    string password;
    public:
    ofstream registrationFile;
    fstream houseInfoFile;
    void Register(){
        string lineToSave;
        cout<<"Welcome, you can now register your account\n";
        cout<<"Initial entry fee will be $500\n";
        cout<<"You will earn 500 credit points after you have successfully create your account\n";
        cout<<"Please enter your username: ";
        getline(cin,username);//so we can read white spaces between words
        cout<<"Please enter your full name: "; 
        getline(cin,fullName);
        cout<<"Please enter your password: "; 
        getline(cin,password);

        bool validInput = false;
        while (validInput != true){
            cout<<"Please enter a valid phone number: ";
            getline(cin,phoneNumber);//so we can read white spaces between number if user enter xxx xxxx xxx
            int nonIntegerCount = 0;
            for (int i = 0; i < phoneNumber.length(); i++){
                if (isdigit(phoneNumber[i]) == false && !isspace(phoneNumber[i])){
                    nonIntegerCount = nonIntegerCount + 1;
                }
            }
            if(nonIntegerCount != 0){
                cout<<"You can only enter integers, try again\n";
                validInput = false;
            }else{
                validInput = true;
            }
        }
        string decision;
        validInput = false;
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
        lineToSave = username + "|" + fullName + "|" + phoneNumber + "|" + creditPoints; 
        registrationFile<<"\n"<<lineToSave;
        registrationFile.close();
        cout<<"Your registration has been complete, you can now log in\n";
        
    }
    void viewHouse(){
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
                //istringstream sstream(subString);
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
    }
};
int main(){ //main method is for testing, remove this once program complete
    User user;
    //user.Register();
    user.viewHouse();
    return 0;
}
