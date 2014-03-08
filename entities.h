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
    ShipEntity(int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(x,y,image)
    {//TODO: move these to .cpp file
        m_cHealth = new KillablePart(health);
        m_cWeapon = new WeaponPart(damage, cooldown);
    }

    //reinisilizes a ship loaded from a save file
    ShipEntity(ifstream *file); //{ load(file); }

    ~ShipEntity();

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //weapon linker functions
    void fire();

    //serialize and write the entity data to the file
    virtual void save(ofstream *file);
    //initilize the entity from a saved file
    virtual void load(ifstream *file);
};

class FactoryEntity : public BaseEntity {

    KillablePart *m_cHealth;
    BuilderPart *m_cBulder;

  public:
    //creates a brand new factory
    FactoryEntity(int x, int y, string image, int health) : BaseEntity(x,y,image)
    {//TODO: move these to .cpp file
        m_cHealth = new KillablePart(health);
        m_cBulder = new BuilderPart("tower");
    }

    //reinisilizes a factory loaded from a save file
    FactoryEntity(ifstream *file);// { load(file); }

    ~FactoryEntity();

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //serialize and write the entity data to the file
    virtual void save(ofstream *file);
    //initilize the entity from a saved file
    virtual void load(ifstream *file);
};


class TowerEntity : public BaseEntity {

    //AngularPart *m_cAngle;

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;

  public:
    //Creates a brand new tower
    TowerEntity(int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(x,y,image)
    {//TODO: move these to .cpp file
        m_cHealth = new KillablePart(health);
        m_cWeapon = new WeaponPart(damage, cooldown);
    }

    //reinisilizes a tower loaded from a save file
    TowerEntity(ifstream *file); //{ load(file); }

    ~TowerEntity();

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //weapon linker functions
    void fire();

    //serialize and write the entity data to the file
    virtual void save(ofstream *file);
    //initilize the entity from a saved file
    virtual void load(ifstream *file);
};

//class for tower contructor components
class ConstructerComponent : public BaseEntity {

  public:
    ConstructerComponent(int x, int y, string image) : BaseEntity(x,y,image)
    {}
};

#endif // ENTITIES_H
