#include <QTimer>
#include <vector>

#include "base_enity.h"
#include "entities.h"

#ifndef MODEL_H
#define MODEL_H

using namespace std;

//class that instatiates, sorts, and containes all enities.
class Map {
//variables
    int id;
    vector<BaseEntity*> all_entities;

    //vector<BaseEntity> all_entities;

//functions
public:
    bool createEntity(string owner, string type, string pos);
    bool killEntity(int id);
    void update();
    //Map* getMap() { return this; }

    int getId() { return id; }
};


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
 //variables
    HighScore *highscores;

    // holds the beginning mother ship and the difficulty setting
    Map* map;

    //used by load to parse a savefile
    //TODO: decide what should be returned by this function.
    void parse();

  public:
    // updates the game (Model) to reflect changes that occured
    void update();

    // initializes the game (Model)
    void initialize();

    //initializes the game from the given file
    Map* load(string filename);

    //serialises game objects and saves them to the given file
    void save(string filename);

    // returns a pointer to the map associated with this Model
    Map* getMap();

};

class Multiuser
{

};


#endif // MODEL_H
