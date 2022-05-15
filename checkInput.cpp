#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using std::string;
using std::cout;
using std::cin;



//check credit only number
bool checkCredit(string input) {
   for (int i = 0; i < input.length(); i++)
   if (isdigit(input[i]) == false)
      return false;
      return true;
};

//check rating -10 to 10
bool checkRating(string input) {
    for (int i = 0; i < input.length(); i++)
   if (isdigit(input[i]) == false) {
       return false;
   }else {
       int s = std::stoi(input);
       if (-10 > s || s > 10) {
           return false;
       } else {
           return true;
       }
   }
    return true;
};

//check city 
bool checkCity(string input, string Arr[3]) {
    for (int i  = 0; i < 3; i++) {
        if (input.compare(Arr[i]) != 0) {
            return false;
        } else {
            return true;
        }
    }
    return true;
}

int main() {
   string str = "f";
    string CityArr[3] = {"Hanoi", "Saigon", "Da Nang"};
   if (checkCity(str, CityArr))
      cout<<str<< " valid";
   else
      cout<<str<< " invalid";


}