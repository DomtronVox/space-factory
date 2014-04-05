//
// highscores.h file
//

#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <vector>
#include <fstream>
#include <QString>
#include <QFile>
#include <sstream>

using namespace std;

//holds data for a single score
class Score{
    string name;
    int score;
public:
    Score(string initName, int initScore) : name(initName), score(initScore) { }

    string toString();

    // getter methods
    string getName() { return name; }
    int getScore() { return score; }

    // adds <scr> to score
    void add(int scr);
};

//class that holds instance variable of names and scores
class HighScore {

private:
    vector<Score*> all_scores;
    QFile* sFile;                // scores file

public:
    // Constructor
    HighScore();

    ~HighScore() {}

    // loads HighScores from a file and populates all_scores
    bool load();

    // saves the HighScores in a txt file
    bool save();

    //adds a Score struct to the score vector.
    bool addScore(string initName, int initScore);
    bool addScore(Score *score);

    // returns the vector containing all the scores
    vector<Score*> getScores() { return all_scores; }

};


#endif // HIGHSCORES_H
