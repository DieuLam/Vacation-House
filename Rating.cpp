#include "header_files/Member.h"
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

// calculate average scores of all ratings
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