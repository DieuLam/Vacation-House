#include "Member.h"
#include "Request.h"
#include "House.h"

Request::Request(Member *sender, House *house, string start, string end)
{
    this->sender = sender;
    this->house = house;
    this->startDate = start;
    this->endDate = end;
}