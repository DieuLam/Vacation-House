#include "header_files/Member.h"
#include "header_files/House.h"
#include "header_files/Rating.h"
#include "header_files/Request.h"
#include "header_files/DataHandler.h"

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
    string username, fullName, password, phoneNumber, lineToSave, creditPoints, occupiedHouse, rater;
    string city, description, startDate, endDate, consummingCredits, minOccRating;
    string comment, score;
    string owner, numDay; // for requests.txt
    fstream saveToFile;

    // This is for saving Member into registrationInfo.txt
    saveToFile.open("files_database/registrationInfo.txt");
    saveToFile << "Username|Fullname|Password|Phone|Credits|HouseOccupied\n";

    for (Member *member : memberList)
    {
        username = member->username;
        fullName = member->fullName;
        password = member->password;
        phoneNumber = member->phone;
        creditPoints = to_string(member->credit);

        if (member->houseOccupied != NULL)
        {
            occupiedHouse = member->houseOccupied->owner->username;
        }
        else
        {
            occupiedHouse = "none";
        }

        lineToSave = username + "|" + fullName + "|" + password + "|" + phoneNumber + "|" + creditPoints + "|" + occupiedHouse;
        saveToFile << lineToSave << "\n";
    }
    saveToFile.close();

    // this is for saving house info to houseInfo.txt
    saveToFile.open("files_database/houseInfo.txt");
    saveToFile << "Owner|City|Description|Start|End|Credits|RequiredRating\n";
    for (House *house : houseInfoList)
    {
        username = house->owner->username;

        city = house->city;
        description = house->description;
        startDate = house->startDate;
        endDate = house->endDate;

        consummingCredits = to_string(house->consummingCredits);
        minOccRating = to_string(house->minOccRating);

        lineToSave = username + "|" + city + "|" + description + "|" + startDate + "|" + endDate + "|" + consummingCredits + "|" + minOccRating;

        saveToFile << lineToSave << "\n";
    }
    saveToFile.close();

    // this is for saving requests to requests.txt
    saveToFile.open("files_database/request.txt");
    saveToFile << "Sender|Owner|Start|End|NumberOfDays\n";
    for (Member *member : memberList)
    {
        vector<Request *> request_per_mem = member->requestSentList;
        for (Request *per_request : request_per_mem)
        {
            username = per_request->sender->username;
            owner = per_request->house->owner->username; // owner of house
            startDate = per_request->startDate;
            endDate = per_request->endDate;
            numDay = to_string(per_request->numDay);

            lineToSave = username + "|" + owner + "|" + startDate + "|" + endDate + "|" + numDay;
            saveToFile << lineToSave << "\n";
        }
    }
    saveToFile.close();

    // this is for saving house ratings to member ratings.txt
    saveToFile.open("files_database/memberRating.txt");
    saveToFile << "Rater|Comment|Scores\n";
    for (Member *member : memberList)
    {
        vector<Rating *> rating_per_mem = member->ratings;
        // rating_per_mem
        for (Rating *per_rating : rating_per_mem)
        {
            username = per_rating->rater->username;
            comment = per_rating->comment;
            score = to_string(per_rating->score);

            lineToSave = username + "|" + comment + "|" + score;
            saveToFile << lineToSave << "\n";
        }
    }
    saveToFile.close();

    // this is for saving member ratings to houseRatings.txt
    saveToFile.open("files_database/houseRating.txt");
    saveToFile << "Rater|Comment|Scores|Owner\n";
    for (House *house : houseInfoList)
    {
        username = house->owner->username;
        vector<Rating *> rating_per_house = house->ratings;
        // rating_per_mem
        for (Rating *per_rating : rating_per_house)
        {
            rater = per_rating->rater->username; // owner username
            comment = per_rating->comment;
            score = to_string(per_rating->score);

            lineToSave = rater + "|" + comment + "|" + score + "|" + username;
            saveToFile << lineToSave << "\n";
        }
    }
    saveToFile.close();
};

void DataHandler::loadFilesToVector(string path, int whichFiles)
{ // load files to its corrospond vectors
    fstream loadToVector;
    string temp;
    string delimeter = "|";

    loadToVector.open(path, ios::in);
    getline(loadToVector, temp);
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
                addMember(new Member(dataPerLine[0], dataPerLine[2], dataPerLine[1], dataPerLine[3], stod(dataPerLine[4]))); // stod turn string to double
                if (dataPerLine[5] != "none")
                {
                    memberList.back()->houseOccupied = new House(new Member(dataPerLine[5], "", "", "", 0), "", "", "", "", 0, 0);
                }
            }

            else if (whichFiles == 2)
            { // houseInfo.txt
                for (Member *member : memberList)
                {
                    if (member->username.compare(dataPerLine[0]) == 0)
                    {
                        member->houseOwned = new House(member, dataPerLine[1], dataPerLine[2], dataPerLine[3], dataPerLine[4], stod(dataPerLine[6]), stod(dataPerLine[5]));
                        addHouse(member->houseOwned);
                    }
                }
            }

            else if (whichFiles == 3)
            { // houseRating.txt
                for (House *house : houseInfoList)
                {
                    if (dataPerLine[3].compare(house->owner->username) == 0)
                    {
                        for (Member *m : memberList)
                        {
                            if (dataPerLine[0].compare(m->username) == 0)
                            {
                                house->ratings.push_back(new Rating(m, dataPerLine[1], stod(dataPerLine[2])));
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            else if (whichFiles == 4)
            { // memberRating.txt
                for (Member *member : memberList)
                {
                    if (dataPerLine[0].compare(member->username) == 0)
                    {
                        for (Member *m : memberList)
                        {
                            if (dataPerLine[0].compare(m->username) == 0)
                            {
                                member->ratings.push_back(new Rating(m, dataPerLine[1], stod(dataPerLine[2])));
                                break;
                            }
                        }
                    }
                }
            }

            else if (whichFiles == 5)
            { // occupiers.txt
                for (Member *m : memberList)
                {
                    if (m->houseOccupied != NULL)
                    {
                        for (Member *m2 : memberList)
                        {
                            if (m->houseOccupied->owner->username.compare(m2->username) == 0)
                            {
                                m->houseOccupied = m2->houseOwned;
                                m2->houseOwned->addOccupier(m);
                            }
                        }
                    }
                }
            }

            else
            { // request.txt
                for (Member *member : memberList)
                {
                    if (dataPerLine[0].compare(member->username) == 0)
                    {
                        for (House *house : houseInfoList)
                        {
                            if (dataPerLine[1].compare(house->owner->username) == 0)
                            {
                                member->requestSentList.push_back(new Request(member, house, dataPerLine[2], dataPerLine[3], stoi(dataPerLine[2]))); // turn string to int
                                house->requestList.push_back(new Request(member, house, dataPerLine[2], dataPerLine[3], stoi(dataPerLine[2])));      // turn string to int
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    loadToVector.close();
};
bool DataHandler::checkMember(string new_username)
{
    for (Member *m : memberList)
    {
        if (m->username.compare(new_username) == 0)
            return false;
    }
    return true;
}
