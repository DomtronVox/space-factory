#include "highscores.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QTextStream>

using namespace std;

bool HighScore::load()
{
    QFile sscores ("://highscores.txt");
    if(sscores.open(QIODevice::ReadOnly))
    {
        string line;
        QTextStream in(&sscores);
        while(!in.atEnd())
        {
            line = in.readLine().toStdString();
            unsigned pos = line.find(":");
            string name = line.substr(0, pos);
            int score = stoi(line.substr(pos + 1));
            Score* aScore = new Score(name, score);
            all_scores.push_back(aScore);
        }
        return true;
    }
    else
    {
        cout << "Unable to open file cotaining highscores, i.e. ://highscores.txt" << endl;
        return false;
    }
}

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


