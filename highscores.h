//
// highscores.h file
//

#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <vector>
#include <fstream>

using namespace std;

//holds data for a single score
struct Score{
    string name;
    int score;
public:
    Score(string initName, int initScore) : name(initName), score(initScore) { }

    // getter methods
    string getName() { return name; }
    int getScore() { return score; }
};

//class that holds instance variable of names and scores
class HighScore {

private:
    fstream scores_file;
    vector<Score*> all_scores;

public:
    // Constructor
    HighScore() {}
    HighScore(string filename) {}

    void sortScores();

    ~HighScore() {}

    // loads HighScores from a file and populates all_scores
    void load();

    // saves the HighScores in a txt file
    void save();

    //adds a Score struct to the score vector.
    void addScore(string name, int score);

    // returns the vector containing all the scores
    vector<Score*> getScores() { return all_scores; }

};


#endif // HIGHSCORES_H
