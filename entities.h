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

    AngularPart *m_cAngle;

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;


  public:
    void update();

    //killable linker functions
    void hit();
    void die();
};

class FactoryEntity : public BaseEntity {

    KillablePart *m_cHealth;

  public:
    void update();

    //killable linker functions
    void hit();
    void die();
};


class TowerEntity : public BaseEntity {

    AngularPart *m_cAngle;

    KillablePart *m_cHealth;
    WeaponPart *m_cWeapon;

  public:
    void update();

    //killable linker functions
    void hit();
    void die();
};

#endif // ENTITIES_H
