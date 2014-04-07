#ifndef MODEL_H
#define MODEL_H

#include <QTimer>
#include <QFile>
#include <vector>
#include <fstream>

#include "highscores.h"
#include "base_entity.h"
#include "entities.h"

using namespace std;

//these are hard coded values used for various variables in the model. These should eventually be moved into a settings or configuration file.
//For now we will keep them centralized here. Try to keep a list of which functions use the constant.
struct Settings{
    Settings(): player_owner("player"), factory_target("tower"), ship_image("blackship1"), enemy_owner("AI"), tower_image("tower")
    {}

//used in model::createTowerand model::createComponent
    string player_owner;

//used in FactoryEntity::FactoryEntity
    static const int factory_counter = 50;
    string factory_target;

//used in model::generateAttacker
    static const int ship_health = 10;
    static const int ship_range = 100;
    static const int ship_damage = 5;
    static const int ship_cooldown = 50;
    string ship_image;
    string enemy_owner;

//used in ShipEntity::ShipEnity
    static const int ship_speed = 10;

//used in model::createTower
    static const int tower_health = 15;
    static const int tower_range = 100;
    static const int tower_size = 55;
    static const int tower_damage = 10;
    static const int tower_cooldown = 50;
    static const int tower_speed = 30;
    string tower_image;


};

//holds the various high level model related classes
class Model {
    Model();

    // current score
    Score *score;

    // file to save a load game from
    QFile *file;
    QFile *sFile;       //scores file

    // difficulty and cheat settings
    QString dif;
    bool cheat;

    // keep track of entities on the game field
    static int id;
    vector<BaseEntity*> all_entities;
    vector<BaseEntity*> recently_created;

    //timer to create enemy ships
    int newWaveTimer;
    int newWaveRange;

    //empty entity list
    void killAllEntities();

protected:
    static Model sInstance;

public:
    static Settings settings;

    //returns a new id to be used by an entity
    static int newId() { return Model::id++; }

    //returns the only instance of world
    static Model* instance() { return &Model::sInstance; }

    //utility function
    void printState();

    //getter methods
    int getScr() { return score->getScore(); }

    //setter methods
    void setDif(QString difficulty) { dif = difficulty; }
    void setCheat(bool cht) { cheat = cht; }
    void setCheat(QString cht);
    void setScr(string na, int scr) { score = new Score(na, scr); }

    // updates the game (Model) to reflect changes that occured
    bool update();

    //initializes the game from the given file
    bool load();

    //serialises game objects and saves them to the given file
    bool save();

    //Sets up model for a singleplayer game
    void singleGameStart(string difficulty, bool cheat);

    //resets whatever game state model has at the moment
    void reset();

    //returns an entity with the given <id> or NULL
    BaseEntity * getById(int id);

    //returns a vector of BaseEntities that have been created recently
    vector<BaseEntity*> getRecentlyCreated();

    //returns a vector of BaseEntities that lie in a certain area
    vector<BaseEntity*> getInArea(int x, int y, int r);

    //returns true if the given area is free of any entities. This ignores component entities.
    bool isAreaEmpty(int x, int y, int r);

    //finilizes entity creation by adding it to the all_entities vector and doing other important things
    void addEntity(BaseEntity * entity);

    //function to randomize the creation of an attacker entity
    void generateWave();

    //function to build a tower
    bool createTower(int x, int y);

    //function to create a component
    void createComponent(string image, string type, int x, int y);

    //function to kill entities
    void killEntity(int id);

    ~Model();
};

class Multiuser
{

};


#endif // MODEL_H
