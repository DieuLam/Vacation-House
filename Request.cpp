// #include "Member.h"
#include "header_files/Request.h"
#include "header_files/House.h"
#include "header_files/Rating.h"

Request::Request(){};

Request::Request(Member *sender, House *house, string start, string end, int numDay)
{
    this->sender = sender;
    this->house = house;
    this->startDate = start;
    this->endDate = end;
    this->numDay = numDay;
}