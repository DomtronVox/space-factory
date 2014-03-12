//
// highscores.h file
//

#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <vector>
#include <fstream>
#include <QString>
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
};

//class that holds instance variable of names and scores
class HighScore {

private:
    vector<Score*> all_scores;

public:
    // Constructor
    HighScore() {}

    ~HighScore() {}

    // loads HighScores from a file and populates all_scores
    bool load();

    // saves the HighScores in a txt file
    bool save();

    //adds a Score struct to the score vector.
    bool addScore(string initName, int initScore);

    // returns the vector containing all the scores
    vector<Score*> getScores() { return all_scores; }

};


#endif // HIGHSCORES_H
