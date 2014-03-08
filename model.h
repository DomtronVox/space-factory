#include <QTimer>
#include <vector>

#include "base_enity.h"
#include "entities.h"

#ifndef MODEL_H
#define MODEL_H

using namespace std;

//class that holds instance variable of names and scores
class HighScore {

private:
    string name;
    int score;

public:
    // Constructor
    HighScore(string initName, int initScore):
        score(initScore), name(initName) { }

    ~HighScore();
};


//holds the various high level model related classes
class Model {
 //singleton design?
    vector<HighScore> highscores;

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
