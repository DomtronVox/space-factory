#include <iostream>

#include "model.h"
#include "base_enity.h"
#include "entities.h"
#include "highscores.h"

Model Model::sInstance;
int Model::id = 0;

//loads highscores and prepairs to hold a game state
Model::Model() {
    HighScore highscores;
    highscores.load();

}

//make sure entity list is empty
Model::~Model()
{
    killAllEntities();
    //delete current_score;
}

//empty entity list
void Model::killAllEntities(){
    for (unsigned int i=0; i < all_entities.size(); i++){
        delete all_entities.at(i);
    }
}

//runs through all the entities and prints them as a string.
void Model::printState(){
    for (BaseEntity *e : all_entities){
        cout << e->stringify() << endl;
    }
}

//tells model a tick has passed and that it should update all entities
void Model::update(){

    for (BaseEntity *e : all_entities){
        e->update();
    }

    //handle creating new ships
    newShipTimer--;
    if (newShipTimer <= 0) {
        generateAttacker();
        newShipTimer = random() % 30 + 40;
    }
}


//Sets up model for a singleplayer game
void Model::singleGameStart(){

    //reset score
    //current_score = new Score("", 0);

    //create the players factory
    FactoryEntity *entity = new FactoryEntity(Model::newId(), 0, 0, "factory", 100);
    addEntity(entity);

    newShipTimer = random() % 30 + 40;
}

//void Model::multiGameStart(){}

//resets whatever game state model has at the moment
void Model::reset()
{
    killAllEntities(); //kill everything
    Model::id = 0; //reset id counter
    //current_score = new Score("", 0);
}

//returns an entity with the given id
BaseEntity * Model::getById(int id)
{
    BaseEntity *found_entity = NULL;

    for (BaseEntity *e : all_entities){
        if (id == e->getId()){
            found_entity = e;
            break;
        }
    }
    return found_entity;
}

//returns a vector of BaseEntities that have been created recently
vector<BaseEntity*> Model::getRecentlyCreated()
{
    vector<BaseEntity*> tmp = recently_created;
    recently_created.clear();
    return tmp;
}

//finilizes entity creation by adding it to the all_entities vector and doing other important things
void Model::addEntity(BaseEntity * entity)
{
    all_entities.push_back(entity);
    recently_created.push_back(entity);
}

//function to randomize the creation of an attacker entity
void Model::generateAttacker()
{
    //generates a random position outside the game window
    int x = random() % 40 + 2500;
    int y = random() % 40 + 2500;

    ShipEntity *ship = new ShipEntity(newId(), x,y, "ship", 10, 2, 20);
    addEntity(ship);
}

//creates a component entity
void Model::createComponent(string type, int x, int y){
    BaseEntity *e = new ComponentEntity(newId(),x,y,type,type);
    addEntity(e);
}


