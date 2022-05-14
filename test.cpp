#include "Member.h"
#include "Rating.h"
#include "House.h"
#include "Request.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>

const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243,
273, 304, 334, 365 };
int countLeapYearDays(int d[]){
   int years = d[2];
   if (d[1] <= 2)
      years--;
   return ( (years / 4) - (years / 100) + (years / 400) );
}
int countNoOfDays(int date1[], int date2[]){
   long int dayCount1 = (date1[2] * 365);
   dayCount1 += monthDays[date1[1]];
   dayCount1 += date1[0];
   dayCount1 += countLeapYearDays(date1);
   long int dayCount2 = (date2[2] * 365);
   dayCount2 += monthDays[date2[1]];
   dayCount2 += date2[0];
   dayCount2 += countLeapYearDays(date2);
   return ( abs(dayCount1 - dayCount2) );
}

// int main()
// {
//     // member date select
//     string startDate;
//     string endDate;
//     char fill = '/';
//     int m_sMonth, m_sYear, m_sDay;
//     int m_eMonth, m_eYear, m_eDay;
//     string city;

//     cout << "Please provide the below information to search for available houses \n\n";
//     // user input city
//     cout << "City: ";
//     cin >> city;
//     // user input start day
//     cout << "Start date (yyyy/mm/dd): ";
//     cin >> startDate;
//     // user input end day
//     cout << "End date (yyyy/mm/dd): ";
//     cin >> endDate;

//     //get day, month, year
//     m_sYear = stoi(startDate.substr(0,4));
//     m_sMonth = stoi(startDate.substr(5,2));
//     m_sDay = stoi(startDate.substr(8,2));

//     m_eYear = stoi(endDate.substr(0,4));
//     m_eMonth = stoi(endDate.substr(5,2));
//     m_eDay = stoi(endDate.substr(8,2));

//     int date1[3] = {m_sDay, m_sMonth, m_sYear};
//     int date2[3] = {m_eDay, m_eMonth, m_eYear};

//     int date3[3] = {13, 5, 2022};
//     int date4[3] = {24, 5, 2022};

//     cout << m_sDay << "/" << m_sMonth << "/" << m_sYear << "\n";
//     cout << m_eDay << "/" << m_eMonth << "/" << m_eYear << "\n";


//     int days = countNoOfDays(date1, date2);

//     cout << days << "\n";

//     cout<<"The number of days between two dates is "<<countNoOfDays(date3, date4);
// };
