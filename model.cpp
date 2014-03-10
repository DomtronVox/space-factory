#include <iostream>

#include "model.h"
#include "base_enity.h"
#include "entities.h"
#include "highscores.h"

Model Model::sInstance;
int Model::id = 0;

//loads highscores and prepairs to hold a game state
Model::Model() {
    //create a high score object and populate it
    //highscores = new HighScore("scores.txt");
    //highscores.load();

}

//make sure entity list is empty
Model::~Model()
{
    killAllEntities();
    delete current_score;
}

//empty entity list
void Model::killAllEntities(){
    for (unsigned int i=0; i < all_entities.size(); i++){
        delete all_entities.at(i);
    }
}

void Model::printState(){
    for (BaseEntity *e : all_entities){
        cout << e->stringify() << endl;
    }
}

//Sets up model for a singleplayer game
void Model::singleGameStart(){

    //reset score
    current_score = new Score("", 0);

    //create the players factory
    FactoryEntity *entity = new FactoryEntity(Model::newId(), 0, 0, "factory", 100);
    all_entities.push_back(entity);
}

//void Model::multiGameStart(){}

//resets whatever game state model has at the moment
void Model::reset(){
    killAllEntities(); //kill everything
    Model::id = 0; //reset id counter
}
