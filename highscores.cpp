#include "highscores.h"

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <QString>

using namespace std;

HighScore::HighScore() {
    sFile = new QFile("highscores.txt");
}

bool HighScore::load() {
    if(sFile->open(QIODevice::ReadOnly))
    {
        string line;
        QTextStream in(sFile);
        while(!in.atEnd()) {
            line = in.readLine().toStdString();
            unsigned pos = line.find(":");
            string name = line.substr(0, pos);
            int score = stoi(line.substr(pos + 1));
            Score* aScore = new Score(name, score);
            all_scores.push_back(aScore);
            cout << "read " << aScore->toString() << " from file." << endl;
        }
        cout << "loaded highscores.txt" << endl;
        sFile->close();
        return true;
    }
    else {
        cout << "Unable to open file cotaining highscores." << endl;
        sFile->close();
        return false;
    }
}

bool HighScore::save() {
    sFile->resize(0);
    if(sFile->open(QIODevice::ReadWrite | QIODevice::Text)) {

        for(int i = 0; i < all_scores.size(); ++i) {
            Score* score = all_scores.at(i);
            QString test(QString::fromStdString(score->toString()));
            QTextStream out(sFile);
            out<<test<<endl;
        }
        sFile->close();
        cout << "saved highscores" << endl;
        return true;

    }
    else { cout << "didn't work" << endl;}
    return false;
}

bool HighScore::addScore(string initName, int initScore) {
    Score* newScore = new Score(initName, initScore);

    if(all_scores.size() == 0) {
        all_scores.insert(all_scores.begin(), newScore);
        return true;
    }

    for(int i = 0; i < all_scores.size(); i++) {
        Score* score = all_scores.at(i);
        if(score->getScore() < initScore) {
            all_scores.insert(all_scores.begin() + i, newScore);
            return true;
        }
    }
    all_scores.push_back(newScore);
    return true;
}

// returns name and score as one string
string Score::toString() {
    string result;
    result.append(name);
    result.append(":");
    result.append(to_string(score));
    return result;
}

// adds <scr> to total score
void Score::add(int scr) {
    score = score + scr;
}
