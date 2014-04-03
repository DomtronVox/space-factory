#ifndef ENTITIES_H
#define ENTITIES_H
#include <string>
#include <fstream>
#include <QFile>
#include "base_entity.h"
#include <iostream>
//part includes
#include "movable_part.h"
#include "angular_part.h"
#include "killable_part.h"
#include "weapon_part.h"
#include "builder_part.h"

using namespace std;

class ShipEntity : public BaseEntity {

    int health, damage, cooldown;
    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;
    MovablePart *m_cMoveable;
    AngularPart *m_cAngular;


public:
    //creates a brand new ship
    ShipEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown);

    ShipEntity();
    //reinisilizes a ship loaded from a save file
    ShipEntity(QFile *file); //{ load(file); }

    ~ShipEntity();

    //returns a string that describes the entity
    string stringify(){
        return "SHIP-ENTITY:" + BaseEntity::stringify() + "," + to_string(health) + "," + to_string(damage) + "," + to_string(cooldown);
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit(int damage) { m_cHealth->hit(damage); }

    //serialize and write the entity data to the file
    void save(QFile *file);
    //initilize the entity from a saved file
    void load(string &line);
};

class FactoryEntity : public BaseEntity {

    int health, damage;
    KillablePart *m_cHealth;
    BuilderPart *m_cBulder;

public:
    //creates a brand new factory
    FactoryEntity(int id, string owner, int x, int y, string image, int health, int damage);

    FactoryEntity();
    //reinisilizes a factory loaded from a save file
    FactoryEntity(QFile *file);// { load(file); }

    ~FactoryEntity();

    //returns a string that describes the entity
    string stringify(){
        return "FACTORY-ENTITY:" + BaseEntity::stringify() + "," + to_string(health) + "," + to_string(damage);
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit(int damage) { m_cHealth->hit(damage); }

    //serialize and write the entity data to the file
    void save(QFile *file);
    //initilize the entity from a saved file
    void load(string &line);

    //runs primary action of the entity
    //TODO: implement this to change component build target
    void primaryAction(int /*x*/, int /*y*/) {}
};


class TowerEntity : public BaseEntity {

    //AngularPart *m_cAngle;

    int health, damage, cooldown;
    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;
    AngularPart *m_cAngular;

public:
    //Creates a brand new tower
    TowerEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown);

    TowerEntity();
    //reinisilizes a tower loaded from a save file
    TowerEntity(QFile *file);

    ~TowerEntity();

    //returns a string that describes the entity
    string stringify(){
        return "TOWER-ENTITY:" + BaseEntity::stringify() + "," + to_string(health) + "," + to_string(damage) + "," + to_string(cooldown);
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit(int damage) { m_cHealth->hit(damage); }

    //weapon linker functions
    void fire();

    //serialize and write the entity data to the file
    void save(QFile *file);
    //initilize the entity from a saved file
    void load(string &line);
};

//class for tower contructor components
class ComponentEntity : public BaseEntity {

    string type;

public:
    ComponentEntity(int id, string owner, int x, int y, string image, string initType) : BaseEntity(id,owner,x,y,image), type(initType)
    {}


    ComponentEntity();

    ~ComponentEntity() {  }

    //returns a string that describes the entity
    string stringify(){
        return "COMPONENT-ENTITY:" + BaseEntity::stringify() + "," + type;
    }

    //tells the entity a tick has passed
    void update() {}

    //serialize and write the entity data to the file
    void save(QFile *file) {}
    //initilize the entity from a saved file
    void load(string &line);

    //runs primary action of the entity
    void primaryAction(int x, int y);
};

#endif // ENTITIES_H
