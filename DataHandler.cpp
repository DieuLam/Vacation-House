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

vector<Member *> DataHandler::memberList;

