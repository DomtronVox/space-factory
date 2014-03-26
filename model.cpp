#include <iostream>
#include <QFile>
#include <QTextStream>
#include "model.h"
#include "base_entity.h"
#include "entities.h"
#include "highscores.h"

Model Model::sInstance;
int Model::id = 0;
Settings Model::settings;

//loads highscores and prepairs to hold a game state
Model::Model() {
    HighScore highscores;
    highscores.load();
    score = new Score("user", 0);
    file = new QFile("SavedGame.txt");
    cout << "file created" << endl;

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

    all_entities.clear();
}

//runs through all the entities and prints them as a string.
void Model::printState(){
    for (BaseEntity *e : all_entities){
        cout << e->stringify() << endl;
    }
}

//tells model a tick has passed and that it should update all entities
void Model::update(){

    for (unsigned int i = 0; i < all_entities.size(); ++i)
    {
        BaseEntity *e = all_entities.at(i);
        e->update();
    }

    //handle creating new ships
    newShipTimer--;
    if (newShipTimer <= 0) {
        generateAttacker();
        newShipTimer = rand() % 30 + 40;
    }
}

bool Model::load()
{
    if(file->open(QIODevice::ReadOnly))
    {

        Model::instance()->reset();
        string line;
        QTextStream in(file);
        while(!in.atEnd())
        {
            line = in.readLine().toStdString();
            unsigned pos = line.find(":");
            string name = line.substr(0, pos);
            line.erase(0, pos + 1);

            if(name == "FACTORY-ENTITY") {
                cout << "Reading Factory Entity " << endl;
                FactoryEntity * fEnt = new FactoryEntity;
                fEnt->load(line);
            }
            else if(name == "COMPONENT-ENTITY"){
                ComponentEntity *cEnt = new ComponentEntity;
                cEnt->load(line);
            }
            else if(name == "SHIP-ENTITY"){
                ShipEntity *sEnt  = new ShipEntity;
                sEnt->load(line);
            }
            else if(name == "TOWER-ENTITY"){
                TowerEntity *tEnt  = new TowerEntity;
                tEnt->load(line);

            }
        }
        Model::id = all_entities.size();
        file->close();
        return true;
    }
    else
    {
        //TO-DO: make program create a QMessageBox if no saved game file exists
        //informing the user of that fact and that he is starting a new game.
        cout << "Unable to open file cotaining saved game, i.e. savedGame.txt" << endl;
        file->close();
        return false;
    }
}

bool Model::save()
{
    file->resize(0);
    if(file->open(QIODevice::ReadWrite | QIODevice::Text)){
        for(unsigned int i = 0; i < all_entities.size(); ++i){
            BaseEntity* ent = all_entities.at(i);
            ent->save(file);
            cout << "entity " << ent->getId() << " saved" << endl;
        }
        file->close();
        return true;
    }
    return false;
}

//Sets up model for a singleplayer game
void Model::singleGameStart(){

    //reset score
    //current_score = new Score("", 0);

    //create the players factory
    FactoryEntity *entity = new FactoryEntity(newId(), Model::settings.player_owner, 0, 0, "factory", 100, 0);
    addEntity(entity);

    newShipTimer = rand() % 30 + 40;
}

//void Model::multiGameStart(){}

//resets whatever game state model has at the moment
void Model::reset()
{
    cout << "all entities cleared" << endl;
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


//returns a vector of BaseEntities that lie in a circle
vector<BaseEntity*> Model::getInArea(int x, int y, int r){
    //entities inside the area
    vector<BaseEntity*> inside;

    for (unsigned int i = 0; i < all_entities.size(); ++i) {

        BaseEntity *e = all_entities.at(i);

        //make sure the entity is not a component
        ComponentEntity* comp = dynamic_cast<ComponentEntity*> (e);
        if (comp == NULL)

            //it's inside the circle if (x-center_x)^2 + (y - center_y)^2 < r^2
            if ( pow(e->getX() - x, 2) + pow(e->getY() - y, 2) <= pow(r, 2) )
                inside.push_back(e);
    }

    return inside;
}


//returns true if the given area is free of any entities. This ignores component entities.
bool Model::isAreaEmpty(int x, int y, int r){
    if (getInArea(x, y, r).size() == 0)  return true;
    else                                 return false;
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
    int x = rand() % 40 + 2000;
    int y = rand() % 40 + 2000;

    ShipEntity *ship = new ShipEntity(newId(), Model::settings.enemy_owner, x,y, Model::settings.ship_image,
                                      Model::settings.ship_health, Model::settings.ship_damage, Model::settings.ship_cooldown);
    addEntity(ship);
}

//create a new tower at the given pos
bool Model::createTower(int x, int y){

   if ( isAreaEmpty(x,y, 35) ){ //TODO: Tower radius. another hardcoded value that needs centralising/removal.
       TowerEntity *tower = new TowerEntity(newId(), Model::settings.player_owner, x,y, Model::settings.tower_image,
                                            Model::settings.tower_health, Model::settings.tower_damage, Model::settings.tower_cooldown);
       addEntity(tower);
       return true;
   } else{
       return false;
   }

}


//creates a component entity
void Model::createComponent(string image, string type, int x, int y){
    BaseEntity *e = new ComponentEntity(newId(), Model::settings.player_owner, x,y,image,type);
    addEntity(e);
}

//kill a single entity by id
void Model::killEntity(int id){
    vector<BaseEntity*>::iterator i;
    for (i = all_entities.begin(); i < all_entities.end(); i++){
        if (id == (*i)->getId()) {
            BaseEntity *bE;
            bE= *i;
            // if killed entity is a ShipEntity
            if(dynamic_cast<ShipEntity*>(bE))
                score->add(5);
            else if(dynamic_cast<TowerEntity*>(bE))
                score->add(-10);
            else if(dynamic_cast<FactoryEntity*>(bE))
                {}//QApplication::quit();

            delete *i;
            all_entities.erase(i);
        }
    }
}
