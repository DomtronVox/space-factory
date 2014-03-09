#include "highscores.h"

using namespace std;

void HighScore::sortScores()
{/*(
    for(int i = 0; i < all_scores.size(); ++i)
    {
        Score* score = all_scores.at(i);
        Score* nextScore = all_scores.at(i+1);
        if(score->getScore() < nextScore->getScore())
        {
            all_scores.insert(all_scores.begin() + i, nextScore);
        }
    }*/
}

void HighScore::addScore(string name, int score)
{
    all_scores.push_back(new Score(name, score));
}

HighScore::HighScore()
{

}

