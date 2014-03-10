#include "model.h"

Model Model::sInstance;

//loads highscores and prepairs to hold a game state
Model::Model() {
    //create a high score object and populate it
    //highscores = new HighScore("scores.txt");
    //highscores.load();

}

Model::~Model()
{
    for (unsigned int i=0; i < all_entities.size(); i++){
        delete all_entities.at(i);
    }
}
