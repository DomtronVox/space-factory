#include "highscores.h"

using namespace std;


bool HighScore::addScore(string initName, int initScore)
{
    Score* newScore = new Score(initName, initScore);

    if(all_scores.size() == 0)
    {
        all_scores.insert(all_scores.begin(), newScore);
        return true;
    }

    for(int i = 0; i < all_scores.size(); i++)
    {
        Score* score = all_scores.at(i);
        if(score->getScore() < initScore)
        {
            all_scores.insert(all_scores.begin() + i, newScore);
            return true;
        }
    }
    all_scores.push_back(newScore);
    return true;
}

