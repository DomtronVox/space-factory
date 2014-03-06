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
    ShipEntity(int x, int y, string image, int health, int damage, int cooldown)
        :BaseEntity(x,y,image), m_cHealth(health), m_cWeapon(damage, cooldown)
    {}

    //reinisilizes a ship loaded from a save file
    ShipEntity(int x, int y, string image, int maxHealth, int curHealth, int damage, int maxCooldown, int curCooldown)
        :BaseEntity(x,y,image), m_cHealth(curHealth, maxHealth), m_cWeapon(damage, maxCooldown, curCooldown)
    {}

    ~ShipEntity();

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //convert the entity to a string so it can be saved
    string serialise();
};

class FactoryEntity : public BaseEntity {

    KillablePart *m_cHealth;
    BuilderPart *m_cBulder;

  public:
    //creates a brand new factory
    FactoryEntity(int x, int y, string image, int health)//, string target)
        :BaseEntity(x,y,image), m_cHealth(health), m_cBulder("tower")
    {}

    //reinisilizes a factory loaded from a save file
    FactoryEntity(int x, int y, string image, int maxHealth, int curHealth, int curCountdown)//, string target)
        :BaseEntity(x,y,image), m_cHealth(maxHealth,curHealth), m_cBulder("tower", curCountdown)
    {}

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //convert the entity to a string so it can be saved
    string serialise();
};


class TowerEntity : public BaseEntity {

    //AngularPart *m_cAngle;

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;

  public:
    //Creates a brand new tower
    TowerEntity(int x, int y, string image, int health, int damage, int cooldown)
            :BaseEntity(x,y,image), m_cHealth(health), m_cWeapon(damage, cooldown)
        {}

    //reinisilizes a tower loaded from a save file
    TowerEntity(int x, int y, string image, int maxHealth, int curHealth, int damage, int maxCooldown, curCooldown)
            :BaseEntity(x,y,image), m_cHealth(maxHealth,curHealth), m_cWeapon(damage, maxCooldown, curCooldown)
        {}

    //tells the entity a tick has passed
    void update();

    //killable linker functions
    void hit();
    void die();

    //convert the entity to a string so it can be saved
    string serialise();
};

#endif // ENTITIES_H
