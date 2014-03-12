#include <QTimer>
#include <vector>
#include <fstream>

#include "highscores.h"
#include "base_enity.h"
#include "entities.h"


#ifndef MODEL_H
#define MODEL_H

using namespace std;

//holds the various high level model related classes
class Model {
    Model();
    ~Model();

    //score tracking
    HighScore *highscores;
    //Score *current_score = new Score(" ", 0); //the players current score

    // keep track of entities on the game field
    static int id;
    vector<BaseEntity*> all_entities;
    vector<BaseEntity*> recently_created;

    //timer to create enemy ships
    int newShipTimer;

    //used by load to parse a savefile
    //TODO: decide what should be returned by this function.
    void parse();

    //empty entity list
    void killAllEntities();

protected:
    static Model sInstance;

public:
    //returns a new id to be used by an entity
    static int newId(){
        return Model::id++;
    }

    //returns the only instance of world
    static Model* instance() { return &Model::sInstance; }

    //utility function
    void printState();

    // updates the game (Model) to reflect changes that occured
    void update();

    //initializes the game from the given file
    void load(string filename);

    //serialises game objects and saves them to the given file
    void save(string filename);

    //Sets up model for a singleplayer game
    void singleGameStart();
    //sets up model for a multyplayer game
    ////void multyGameStart();
    //resets whatever game state model has at the moment
    void reset();

    //returns an entity with the given <id> or NULL
    BaseEntity * getById(int id);

    //returns a vector of BaseEntities that have been created recently
    vector<BaseEntity*> getRecentlyCreated();

    //finilizes entity creation by adding it to the all_entities vector and doing other important things
    void addEntity(BaseEntity * entity);

    //function to randomize the creation of an attacker entity
    void generateAttacker();

    //function to build a tower
    bool createTower(int x, int y);

    //function to create a component
    void createComponent(string image, string type, int x, int y);

    //function to kill entities
    bool killEntity(int id);


};

class Multiuser
{

};


#endif // MODEL_H
