#include <QTimer>
#include <vector>

#include "base_enity.h"
#include "entities.h"

#ifndef MODEL_H
#define MODEL_H

using namespace std;

//class that loads, adds to, holds, and saves highscores
class HighScore {
//variables
    string filename; //should we have this be a file object?
    vector<string> names;
    vector<int> scores;

//functions
public:
    HighScore(string filename);
    ~HighScore();

    //serializes names and scores then writes them to the scores file
    bool save();
    //parses all data in the scores file and populates names and scores
    bool load();
    //adds a score to the scores list. Sorts by score so high scores are near the begining.
    bool addScore(string name, int score);
    //returns all names
    vector<string> getNames();
    //returns all scores
    vector<int> getScores();
};


//holds the various high level model related classes
class Model {
 //singleton design?

    //links to the highscores instance
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
