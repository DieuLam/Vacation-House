#include <iostream>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::vector;

class Member;
class House;

class Rating
{
private:
    Member *rater;
    string comment;
    double score;

public:
    Rating();

    Rating(Member *m, string comment, double score);

    static  double calculateScores(vector<Rating *> ratings);
    friend class Member;
    friend class House;
    // friend class DataHandler;
};

