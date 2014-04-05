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

/*
Settings::~Settings(){
    delete[] enemy_owner;
    delete[] player_owner;
    delete[] factory_target;
    delete[] ship_image;
    delete[] tower_image;
}
*/

//loads highscores and prepares to hold a game state
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

void Model::setCheat(QString cht)
{
    if(cht == "true")
        cheat = true;
    else
        cheat = false;
}

void Model::setScr(QString na, QString scr){
    score = new Score(na.toStdString(), scr.toInt() );
}


//tells model a tick has passed and that it should update all entities
bool Model::update(){

    for (unsigned int i = 0; i < all_entities.size(); ++i)
    {
        BaseEntity *e = all_entities.at(i);
        e->update();
    }

    //handle creating new ships
    newWaveTimer--;
    if (newWaveTimer <= 0) {
        generateWave();
        newWaveTimer = rand() % 30 + newWaveRange;
    }

    if (getById(0) == NULL) return false;
    else                    return true;
}

bool Model::load()
{
    if(file->open(QIODevice::ReadOnly))
    {
        Model::instance()->reset();
        string line;
        QTextStream in(file);
        line = in.readLine().toStdString();
        unsigned nPos = line.find(" ");
        Model::instance()->setDif(QString::fromStdString(line.substr(0, nPos)));
        Model::instance()->setCheat(QString::fromStdString(line.substr(nPos+1)));
        line = in.readLine().toStdString();
        Model::instance()->setScr(QString::fromStdString(line.substr(0, nPos = line.find(" "))), QString::fromStdString(line.substr(nPos + 1)));
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
        BaseEntity *be = all_entities.back();
        Model::id = be->getId() + 1;
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
        QString cheatStr;
        if(cheat){
            cheatStr = "true";
        }
        else { cheatStr = "false"; }
        QString data = dif + " " + cheatStr;
        QTextStream out(file);
        out << data << endl;
        data = QString::fromStdString(score->getName()) + " " + QString::number(score->getScore());
        out << data << endl;
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
void Model::singleGameStart(string difficulty, bool cheat){

    //reset score
    //current_score = new Score("", 0);

    //create the players factory
    FactoryEntity *factory;
    if (difficulty == "easy") {
        factory = new FactoryEntity(0, Model::settings.player_owner, 0, 0, "factory", 200, 0);
        newWaveRange = 40;
    } else if (difficulty == "medium") {
        factory = new FactoryEntity(0, Model::settings.player_owner, 0, 0, "factory", 100, 0);
        newWaveRange = 30;
    } else {
        factory = new FactoryEntity(0, Model::settings.player_owner, 0, 0, "factory", 50, 0);
        newWaveRange = 10;
    }

    if (cheat) {
        //0 health = infinate health
        factory = new FactoryEntity(0, Model::settings.player_owner, 0, 0, "factory", 0, 0);
    }

    newId(); //since we manuely set the id run newId to advance the entity id

    addEntity(factory);

    newWaveTimer = rand() % 30 + newWaveRange;
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
void Model::generateWave()
{
    //TODO: generate multiple ships not just one; fix it so ships apeare anyware beyond the screen edge
    //generates a random position outside the game window
    int x = rand() % 20 + 1500;
    int y = rand() % 20 + 1500;
    //randomize x and y's sign
    int sx = rand() % 3 - 1;
    int sy = rand() % 3 - 1;

    //problem where if both signs are 0 the ship apears at the factory
    if (sx == 0 && sy == 0) sx = 1;

    ShipEntity *ship = new ShipEntity(newId(), Model::settings.enemy_owner, sx*x, sy*y, Model::settings.ship_image,
                                      Model::settings.ship_health, Model::settings.ship_damage, Model::settings.ship_cooldown);
    addEntity(ship);
}

//create a new tower at the given pos
bool Model::createTower(int x, int y){

   if ( isAreaEmpty(x,y, Model::settings.tower_size) ){
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
