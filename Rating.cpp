#include "Member.h"
#include "Rating.h"

Rating::Rating(Member *m, string comment, double score)
{
    this->rater = m;
    this->comment = comment;
    this->score = score;
}

double Rating::calculateScores(vector<Rating *> ratings)
{
    double sum = 0;
    for (Rating *r : ratings)
    {
        sum += r->score;
    }
    return sum / ratings.size();
}