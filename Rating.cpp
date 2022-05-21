// #include "Member.h"
#include "header_files/Rating.h"
#include "header_files/House.h"
#include "header_files/Request.h"

Rating::Rating(){};

Rating::Rating(Member *m, string comment, double score)
{
    this->rater = m;
    this->comment = comment;
    this->score = score;
}

double Rating::calculateScores(vector<Rating *> ratings)
{
    double sum = 0;
    if (!ratings.empty())
    {
        for (Rating *r : ratings)
        {
            sum += r->score;
        }
        return sum / ratings.size();
    }
    return sum;
}