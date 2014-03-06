#include <QTimer>

#include "base_enity.h"
#include "entities.h"

#ifndef MODEL_H
#define MODEL_H


//class that instatiates, sorts, and containes all enities.
class Map {
//variables
    static id = 0;
    vector<BaseEntity*> all_entities;
    vector<BaseEntity*>;

//functions
    bool createEntity(owner, type, pos);
    bool killEntity(id);
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
    HighScore(filename);
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
    Map* map;

  public:

};

class Multiuser
{

};


#endif // MODEL_H
