#include <string>

#include "entities.h"

//part includes
#include "angular_part.h"
#include "killable_part.h"
#include "weapon_part.h"
#include "builder_part.h"


//ship functions
ShipEntity::ShipEntity(int id, int x, int y, char* image, int health, int damage, int cooldown) : BaseEntity(id,x,y,image)
{
    m_cHealth = new KillablePart(health);
    m_cWeapon = new WeaponPart(damage, cooldown);
}

ShipEntity::~ShipEntity()
{
    delete m_cHealth;
    delete m_cWeapon;
}

void ShipEntity::update()
{

}

//factory functions
FactoryEntity::FactoryEntity(int id, int x, int y, char* image, int health) : BaseEntity(id,x,y,image)
{
    m_cHealth = new KillablePart(health);
    m_cBulder = new BuilderPart("tower");
}

FactoryEntity::~FactoryEntity()
{
    delete m_cBulder;
    delete m_cHealth;
}

void FactoryEntity::update()
{
    m_cBulder->tick(x,y);
}

//tower functions
TowerEntity::TowerEntity(int id, int x, int y, char* image, int health, int damage, int cooldown) : BaseEntity(id,x,y,image)
{
    m_cHealth = new KillablePart(health);
    m_cWeapon = new WeaponPart(damage, cooldown);
}

TowerEntity::~TowerEntity()
{
    delete m_cHealth;
    delete m_cWeapon;
}

void TowerEntity::update(){

}
