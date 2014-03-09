#include "highscores.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <QString>

using namespace std;

bool HighScore::load()
{
    QFile sscores ("highscores.txt");
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
            cout << "read " << aScore->toString() << " from file." << endl;
        }
        sscores.close();
        return true;
    }
    else
    {
        cout << "Unable to open file cotaining highscores, i.e. ://highscores.txt" << endl;
        sscores.close();
        return false;
    }
}

bool HighScore::save()
{
    QFile sFile ("highscores.txt");

    if(sFile.open(QIODevice::ReadWrite | QIODevice::Text)) {

        for(int i = 0; i < all_scores.size(); ++i)
        {
            Score* score = all_scores.at(i);
            QString test(QString::fromStdString(score->toString()));
            QTextStream out(&sFile);
            out<<test<<endl;
        }
        sFile.close();
        return true;

    }
    else { cout << "didn't work" << endl;}
    return false;
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




string Score::toString()
{
    string result;
    result.append(name);
    result.append(":");
    result.append(to_string(score));
    return result;
}
