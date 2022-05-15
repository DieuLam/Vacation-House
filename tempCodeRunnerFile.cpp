const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243,
// 273, 304, 334, 365 };
// int countLeapYearDays(int d[]){
//    int years = d[2];
//    if (d[1] <= 2)
//       years--;
//    return ( (years / 4) - (years / 100) + (years / 400) );
// }
// int countNoOfDays(int date1[], int date2[]){
//    long int dayCount1 = (date1[2] * 365);
//    dayCount1 += monthDays[date1[1]];
//    dayCount1 += date1[0];
//    dayCount1 += countLeapYearDays(date1);
//    long int dayCount2 = (date2[2] * 365);
//    dayCount2 += monthDays[date2[1]];
//    dayCount2 += date2[0];
//    dayCount2 += countLeapYearDays(date2);
//    return ( abs(dayCount1 - dayCount2) );
// }