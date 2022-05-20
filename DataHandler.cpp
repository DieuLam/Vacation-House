#include "Member.h"
#include "House.h"
#include "Rating.h"
#include "Request.h"
#include "DataHandler.h"

DataHandler::DataHandler(){};

void DataHandler::addMember(Member *member)
{
    memberList.push_back(member);
};
void DataHandler::addHouse(House *house)
{
    houseInfoList.push_back(house);
};
vector<House *> DataHandler::houseInfoList;
vector<Member *> DataHandler::memberList;

void DataHandler::saveVectorsToFile()
{ // load vectors to its corrospond files
    string username, fullName, password, phoneNumber, lineToSave, creditPoints, houseOccupied;
    string city, description, startDate, endDate, consummingCredits, minOccRating;

    fstream saveTo_registrationInfo, saveTo_houseInfo;

    // This is for saving Member into registrationInfo.txt
    saveTo_registrationInfo.open("files_database/registrationInfo.txt");

    for (Member *member : memberList)
    {
        username = member->username;
        fullName = member->fullName;
        password = member->password;
        phoneNumber = member->phone;
        creditPoints = to_string(member->credit);
        houseOccupied = member->houseOccupied->owner->username;

        lineToSave = username + "|" + fullName + "|" + password + "|" + phoneNumber + "|" + creditPoints + "|" + houseOccupied;
        saveTo_registrationInfo << "\n"
                                << lineToSave;
    }
    saveTo_registrationInfo.close();

    // this is for saving house info to houseInfo.txt
    saveTo_houseInfo.open("files_database/houseInfo.txt");
    for (House *house : houseInfoList)
    {

        username = house->owner->username;
        fullName = house->owner->fullName;
        password = house->owner->password;
        phoneNumber = house->owner->phone;
        creditPoints = to_string(house->owner->credit);

        city = house->city;
        description = house->description;
        startDate = house->startDate;
        endDate = house->endDate;
        consummingCredits = to_string(house->consummingCredits);
        minOccRating = to_string(house->minOccRating);

        lineToSave = username + "|" + fullName + "|" + password + "|" + phoneNumber + "|" + creditPoints + "|" + city + "|" + description + "|" + startDate + "|" + endDate + "|" + consummingCredits + "|" + minOccRating;

        saveTo_houseInfo << "\n"
                         << lineToSave;
    }
    saveTo_houseInfo.close();

    // this is for saving requests to requests.txt
    // saveToFile.open("files_database/registrationInfo.txt");

    // saveToFile.close();
    // this is for saving house ratings to house ratings.txt

    // this is for saving member ratings to memberRatings.txt
};

void DataHandler::loadFilesToVector(string path, int whichFiles)
{ // load files to its corrospond vectors
    fstream loadToVector;
    string temp;
    string delimeter = "|";

    loadToVector.open(path, ios::in);

    while (getline(loadToVector, temp))
    { // save line to string temp
        size_t pos = 0;
        string subString;
        if (!temp.empty())
        {
            vector<string> dataPerLine; // save each element into a vector
            while ((pos = temp.find(delimeter)) != std::string::npos)
            {                                            // use find() here to get position of delimiters
                subString = temp.substr(0, pos);         // subString is equals to all string up to delimiter '|'
                dataPerLine.push_back(subString);        // put the subString into the vector
                temp.erase(0, pos + delimeter.length()); // delete the subString from the line so the next subString won't be repeated
            }
            dataPerLine.push_back(temp);

            if (whichFiles == 1)
            {
                addMember(new Member(dataPerLine[0], dataPerLine[2], dataPerLine[1], dataPerLine[3], stoi(dataPerLine[4]))); // stoi() turn string credits = int credit
                memberList.back()->houseOccupied->owner = new Member(dataPerLine[5],"","",0,0);
            }
            else if (whichFiles == 2)
            { // houseInfo.txt
                for (Member *member : memberList)
                {
                    if (member->username.compare(dataPerLine[0]) == 0 && member->fullName.compare(dataPerLine[1]) == 0 && member->password.compare(dataPerLine[2]) == 0)
                    {
                        member->houseOwned = new House(member, dataPerLine[5], dataPerLine[6], dataPerLine[7], dataPerLine[8], stod(dataPerLine[9]), stod(dataPerLine[10]));
                        addHouse(member->houseOwned);
                    }
                }
            }
            else if (whichFiles == 3)
            { // houseRating.txt
              // to do rating, do it like saving houseInfo.txt
              // trong moi class House và Member co vector Rating rieng
              // vector rating trong Member là member rating, trong house là house
              // rating.
            }
            else if (whichFiles == 4)
            { // memberRating.txt
            }
            else if (whichFiles == 5)
            { 
                for (Member *m : memberList) {
                    for (Member *m2 : memberList) {
                        if (m->houseOccupied->owner->username.compare(m2->username) == 0) {
                            m->houseOccupied = m2->houseOwned;
                            m2->houseOwned->occupierList.push_back(m);
                        }
                    }
                }
            }
            else if (whichFiles == 6)
            { // requests.txt
            }
            else
            {
            }
        }
    }
    loadToVector.close();
};
