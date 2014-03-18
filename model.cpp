#include <iostream>
#include <QFile>
#include <QTextStream>
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
    QFile sFile ("savedGame.txt");
    if(sFile.open(QIODevice::ReadOnly))
    {
        Model::instance()->reset();
        string line;
        QTextStream in(&sFile);
        while(!in.atEnd())
        {
            line = in.readLine().toStdString();
            unsigned pos = line.find(":");
            string name = line.substr(0, pos);
            line.erase(0, pos + 1);
            string Eid = line.substr(0, pos = line.find(","));
            line.erase(0,pos + 1);
            string x = line.substr(0, pos = line.find(","));
            line.erase(0,pos + 1);
            string y = line.substr(0, pos = line.find(","));
            line.erase(0,pos + 1);
            string image = line.substr(0, pos = line.find(","));
            line.erase(0,pos + 1);

            cout << name << " " << x << " " << y << endl;
            if(name == "FACTORY-ENTITY")
            {
                string health = line.substr(0, pos = line.find(","));
                line.erase(0, pos + 1);
                string damage = line.substr(0, pos = line.find(","));
                FactoryEntity* ent = new FactoryEntity(stoi(Eid), "player", stoi(x), stoi(y), image, stoi(health), stoi(damage));
                Model::instance()->addEntity(ent);
                cout << "loaded FACTORY" << endl;
            }
            else if (name == "SHIP-ENTITY")
                {
                string health = line.substr(0, pos = line.find(","));
                line.erase(0, pos + 1);
                string damage = line.substr(0, pos = line.find(","));
                line.erase(0, pos + 1);
                string cooldown = line.substr(0, pos = line.find(","));
                line.erase(0, pos + 1);
                ShipEntity* ent = new ShipEntity(stoi(Eid), "AI", stoi(x), stoi(y), image, stoi(health), stoi(damage), stoi(cooldown));
                Model::instance()->addEntity(ent);
                cout << "loaded SHIP-ENTITY" << endl;

                }
            else if( name == "COMPONENT-ENTITY")
                {
                string type = line.substr(0, pos = line.find(","));
                line.erase(0, pos + 1);
                string damage = line.substr(0, pos = line.find(","));
                line.erase(0, pos + 1);
                ComponentEntity* ent = new ComponentEntity(stoi(Eid), "player", stoi(x), stoi(y), image, type);
                Model::instance()->addEntity(ent);
                cout << "loaded COMPONENT-ENTITY" << endl;
                }
            else {
                cout << "unable to load line" << endl;
            }
        }
        Model::id = all_entities.size();
        sFile.close();
        return true;
    }
    else
    {
        //TO-DO: make program create a QMessageBox if no saved game file exists
        //informing the user of that fact and that he is starting a new game.
        cout << "Unable to open file cotaining saved game, i.e. savedGame.txt" << endl;
        sFile.close();
        return false;
    }
}

bool Model::save()
{
    if(remove("savedGame.txt") == 0)
        cout << "savedGame.txt succesfully removed" << endl;
    QFile sFile ("savedGame.txt");

    if(sFile.open(QIODevice::ReadWrite | QIODevice::Text)) {

        for(int i = 0; i < all_entities.size(); ++i)
        {
            BaseEntity* entity = all_entities.at(i);
            QString data(QString::fromStdString(entity->stringify()));
            QTextStream out(&sFile);
            out << data << endl;
        }
        sFile.close();
        return true;

    }
    sFile.close();
    return false;
}


//Sets up model for a singleplayer game
void Model::singleGameStart(){

    //reset score
    //current_score = new Score("", 0);

    //create the players factory
    FactoryEntity *entity = new FactoryEntity(newId(), "player", 0, 0, "factory", 100, 0);
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

    ShipEntity *ship = new ShipEntity(newId(), "AI", x,y, "ship", 10, 2, 50);
    addEntity(ship);
}

//create a new tower at the given pos
bool Model::createTower(int x, int y){

   if ( isAreaEmpty(x,y, 35) ){ //TODO: Tower radius. another hardcoded value that needs centralising/removal.
       TowerEntity *tower = new TowerEntity(newId(), "player", x,y, "tower", 100, 10, 50);
       addEntity(tower);
       return true;
   } else{
       return false;
   }

}


//creates a component entity
void Model::createComponent(string image, string type, int x, int y){
    BaseEntity *e = new ComponentEntity(newId(), "player", x,y,image,type);
    addEntity(e);
}

//kill a single entity by id
void Model::killEntity(int id){
    vector<BaseEntity*>::iterator i;
    for (i = all_entities.begin(); i < all_entities.end(); i++){
        if (id == (*i)->getId()) {
            delete *i;
            all_entities.erase(i);
        }
    }
}
