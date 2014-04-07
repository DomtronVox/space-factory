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

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;
    MovablePart *m_cMoveable;
    AngularPart *m_cAngular;


public:
    //creates a brand new ship
    ShipEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown);

    //reinisilizes a ship loaded from a save file line string
    ShipEntity(string &line);

    ~ShipEntity();

    //returns a string that describes the entity
    string stringify(){
        return "SHIP-ENTITY:" + BaseEntity::stringify() + "," + m_cHealth->stringify() + "," + m_cWeapon->stringify() + "," + m_cMoveable->stringify() + "," + m_cAngular->stringify() + ",";
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit(int damage) { m_cHealth->hit(damage); }
};

class FactoryEntity : public BaseEntity {

    KillablePart *m_cHealth;
    BuilderPart *m_cBulder;

public:
    //creates a brand new factory
    FactoryEntity(int id, string owner, int x, int y, string image, int health);

    //reinisilizes a factory loaded from a save file line string
    FactoryEntity(string &line);

    ~FactoryEntity();

    //returns a string that describes the entity
    string stringify(){
        return "FACTORY-ENTITY:" + BaseEntity::stringify() + "," + m_cHealth->stringify() + "," + m_cBulder->stringify() + ",";
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit(int damage) { m_cHealth->hit(damage); }

    //runs primary action of the entity
    //TODO: implement this to change component build target
    void primaryAction(int /*x*/, int /*y*/) {}
};


class TowerEntity : public BaseEntity {

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;
    AngularPart *m_cAngular;

public:
    //Creates a brand new tower
    TowerEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown);

    //reinisilizes a tower loaded from a save file line string
    TowerEntity(string &line);

    ~TowerEntity();

    //returns a string that describes the entity
    string stringify(){
        return "TOWER-ENTITY:" + BaseEntity::stringify() + "," + m_cHealth->stringify() + "," + m_cWeapon->stringify() + "," + m_cAngular->stringify() + ",";
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit(int damage) { m_cHealth->hit(damage); }

    //weapon linker functions
    void fire();
};

//class for tower contructor components
class ComponentEntity : public BaseEntity {

    string type;

public:
    //Creates a brand new component
    ComponentEntity(int id, string owner, int x, int y, string image, string initType) : BaseEntity(id,owner,x,y,image), type(initType)
    {}

    //reinisilizes a component loaded from a save file line string
    ComponentEntity(string &line);

    ~ComponentEntity() {  }

    //returns a string that describes the entity
    string stringify(){
        return "COMPONENT-ENTITY:" + BaseEntity::stringify() + "," + type + ",";
    }

    //tells the entity a tick has passed
    void update() {}

    //runs primary action of the entity
    void primaryAction(int x, int y);
};

#endif // ENTITIES_H
