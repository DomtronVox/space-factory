#include "highscores.h"

using namespace std;


void HighScore::addScore(string name, int score)
{
    all_scores.push_back(new Score(name, score));
}

