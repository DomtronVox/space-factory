#include <string>

#include "entities.h"

//part includes
#include "movable_part.h"
#include "angular_part.h"
#include "killable_part.h"
#include "weapon_part.h"
#include "builder_part.h"

//TODO: change code that needs model and remove this include
#include "model.h"


//ship functions
ShipEntity::ShipEntity(int id, int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(id,x,y,image)
{
    ShipEntity::health = health;
    ShipEntity::damage = damage;
    ShipEntity::cooldown = cooldown;
    m_cHealth = new KillablePart(health);
    m_cWeapon = new WeaponPart(damage, cooldown);
    m_cMoveable = new MovablePart(10, 0, 0, id);
}

ShipEntity::~ShipEntity()
{
    delete m_cHealth;
    delete m_cWeapon;
    delete m_cMoveable;
}

void ShipEntity::update()
{
    m_cMoveable->tick(this);
}

//factory functions
FactoryEntity::FactoryEntity(int id, int x, int y, string image, int health, int damage) : BaseEntity(id,x,y,image)
{
    FactoryEntity::health = health;
    FactoryEntity::damage = damage;
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
TowerEntity::TowerEntity(int id, int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(id,x,y,image)
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

//runs primary action of the entity
void ComponentEntity::primaryAction(int x, int y) {

    if(Model::instance()->createTower(x,y)) Model::instance()->killEntity(id);
}
