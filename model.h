#include <QTimer>

#include "base_enity.h"
#include "entities.h"

#ifndef MODEL_H
#define MODEL_H

using namespace std;

//class that instatiates, sorts, and containes all enities.
class Map {
//variables
<<<<<<< HEAD
    static id = 0;
    vector<BaseEntity*> all_entities;
    vector<BaseEntity*>;
=======
    int id;
    vector<BaseEntity> all_entities;
>>>>>>> f495a75f02772e46e2a9b82ca9e3e61450e9ad07

//functions
    bool createEntity(string owner, string type, string pos);
    bool killEntity(int id);
    void update();
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
    bool save();
    bool load();
    bool addScore();
};

//holds the various high level model related classes
class Model {
 //singleton design?
 //variables
    HighScore *highscores;

    // holds the beginning mother ship and the difficulty setting
    Map* map;

  public:
    // updates the game (Model) to reflect changes that occured
    void update();

    // initializes the game (Model)
    void initialize();

};

class Multiuser
{

};


#endif // MODEL_H
