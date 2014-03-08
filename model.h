#include <QTimer>
#include <vector>
#include <fstream>

#include "base_enity.h"
#include "entities.h"


#ifndef MODEL_H
#define MODEL_H

using namespace std;

//holds data for a single score
struct Score{
    string name;
    int score;
};

//class that holds instance variable of names and scores
class HighScore {

private:
    fstream scores_file;
    vector<Score> all_scores;

public:
    // Constructor
    HighScore(string filename);

    ~HighScore();

    //adds a Score struct to the score vector.
    void addScore(string name, int score);
};


//holds the various high level model related classes
class Model {
 //singleton design?
    HighScore *highscores;

    // keep track of entities on the game field
    static int id;
    vector<BaseEntity*> all_entities;

    //used by load to parse a savefile
    //TODO: decide what should be returned by this function.
    void parse();

  public:
    // updates the game (Model) to reflect changes that occured
    void update();

    // initializes the Model
    void initialize();

    //initializes the game from the given file
    void load(string filename);

    //serialises game objects and saves them to the given file
    void save(string filename);

    //functions to create and kill entities
    bool createEntity(string owner, string type, string pos);
    bool killEntity(int id);

};

class Multiuser
{

};


#endif // MODEL_H
