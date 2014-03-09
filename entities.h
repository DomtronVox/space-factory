#include <string>
#include <fstream>

#include "base_enity.h"

//part includes
#include "angular_part.h"
#include "killable_part.h"
#include "weapon_part.h"
#include "builder_part.h"

#ifndef ENTITIES_H
#define ENTITIES_H

using namespace std;

class ShipEntity : public BaseEntity {

    //AngularPart *m_cAngle;

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;

    //MovablePart *m_cMove //TODO: finish movablepart


public:
    //creates a brand new ship
    ShipEntity(int id, int x, int y, char* image, int health, int damage, int cooldown);

    //reinisilizes a ship loaded from a save file
    ShipEntity(ifstream *file); //{ load(file); }

    ~ShipEntity();

    //returns a string that describes the entity
    string stringify(){
        return "ShipEntity:"+to_string(id)+","+to_string(x)+","+to_string(y)+","+image;
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //weapon linker functions
    void fire();

    //serialize and write the entity data to the file
    void save(ofstream *file) {}
    //initilize the entity from a saved file
    void load(ifstream *file) {}
};

class FactoryEntity : public BaseEntity {

    KillablePart *m_cHealth;
    BuilderPart *m_cBulder;

public:
    //creates a brand new factory
    FactoryEntity(int id, int x, int y, char* image, int health);

    //reinisilizes a factory loaded from a save file
    FactoryEntity(ifstream *file);// { load(file); }

    ~FactoryEntity();

    //returns a string that describes the entity
    string stringify(){
        return "FactoryEntity:"+to_string(id)+","+to_string(x)+","+to_string(y)+","+image;
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //serialize and write the entity data to the file
    void save(ofstream *file) {}
    //initilize the entity from a saved file
    void load(ifstream *file) {}
};


class TowerEntity : public BaseEntity {

    //AngularPart *m_cAngle;

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;

public:
    //Creates a brand new tower
    TowerEntity(int id, int x, int y, char* image, int health, int damage, int cooldown);

    //reinisilizes a tower loaded from a save file
    TowerEntity(ifstream *file); //{ load(file); }

    ~TowerEntity();

    //returns a string that describes the entity
    string stringify(){
        return "TowerEntity:"+to_string(id)+","+to_string(x)+","+to_string(y)+","+image;
    }

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //weapon linker functions
    void fire();

    //serialize and write the entity data to the file
    void save(ofstream *file) {}
    //initilize the entity from a saved file
    void load(ifstream *file) {}
};

//class for tower contructor components
class ComponentEntity : public BaseEntity {

    char* type;

public:
    ComponentEntity(int id, int x, int y, char* image, char* initType) : BaseEntity(id,x,y,image), type(initType)
    {}

    ~ComponentEntity() {  }

    //returns a string that describes the entity
    string stringify(){
        return "ComponentEntity:"+to_string(id)+","+to_string(x)+","+to_string(y)+","+image+","+type;
    }
};

#endif // ENTITIES_H
