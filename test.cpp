#include "Member.h"
#include "Rating.h"
#include "House.h"
#include "Request.h"
#include <algorithm>
#include <iostream>
#include <string>

void Member::checkAvailableHouses(Member *member)
{
    //member date select
        string startDate;
        string endDate;
        char fill = '/';
        int m_sMonth, m_sYear, m_sDay;
        int m_eMonth, m_eYear, m_eDay;


        //user input start day
        cout << "Please provide the below information to search for available houses \n\n";
        cout << "Start date (yyyy/mm/dd): ";
        cin >> startDate;

        //user input end day
        cout << "End date (yyyy/mm/dd): ";
        cin >> endDate;


        //get day, month, year
        // m_sYear = stoi(startDate.substr(0,2));
        // m_sMonth = stoi(startDate.substr(3,2));
        // m_sDay = stoi(startDate.substr(6));

        // m_eYear = stoi(endDate.substr(0,2));
        // m_eMonth = stoi(endDate.substr(3,2));
        // m_eDay = stoi(endDate.substr(6));

    std::fstream houseInfoFile;
    houseInfoFile.open("houseInfo.txt",std::ios::in); //ios::in to open file performing read operations
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

        for (int i = 0; i < printInfo.size(); i++) {
            if(endDate < startDate) {
                cout << "invalid date!!!";
                return;
            } else {
                if ((printInfo[4] >= startDate && startDate <= printInfo[5]) && (printInfo[4] >= endDate && endDate <= printInfo[5])) {
                    cout << printInfo[0];
                }
            }
        }
    }
    houseInfoFile.close();
};
