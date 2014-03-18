#include <string>
#include <QTextStream>
#include <QDebug>
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

ShipEntity::ShipEntity()
{

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

void ShipEntity::save(QFile *file)
{

}

void ShipEntity::load(string &line)
{
     int pos;
     BaseEntity::load(line);
     ShipEntity::health = stoi(line.substr(0, pos = line.find(",")));
     line.erase(0, pos + 1);
     ShipEntity::damage = stoi(line.substr(0, pos = line.find(",")));
     line.erase(0, pos + 1);
     ShipEntity::cooldown = stoi(line.substr(0, pos = line.find(",")));
     line.erase(0, pos + 1);
     Model::instance()->addEntity(this);
     cout << "loaded SHIP-ENTITY" << endl;

}

//factory functions
FactoryEntity::FactoryEntity(int id, int x, int y, string image, int health, int damage) : BaseEntity(id,x,y,image)
{
    FactoryEntity::health = health;
    FactoryEntity::damage = damage;
    m_cHealth = new KillablePart(health);
    m_cBulder = new BuilderPart("tower");

}

FactoryEntity::FactoryEntity()
{

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

void FactoryEntity::save(QFile *file)
{

}

void FactoryEntity::load(string &line)
{
    int pos;
    BaseEntity::load(line);
    FactoryEntity::health = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    FactoryEntity::damage = stoi(line.substr(0, pos = line.find(",")));
    Model::instance()->addEntity(this);
    cout << "FactEnt added" << endl;
}

//tower functions
TowerEntity::TowerEntity(int id, int x, int y, string image, int health, int damage, int cooldown)
    : BaseEntity(id,x,y,image)
{
    TowerEntity::health = health;
    TowerEntity::damage = damage;
    TowerEntity::cooldown = cooldown;
    m_cHealth = new KillablePart(health);
    m_cWeapon = new WeaponPart(damage, cooldown);
}

TowerEntity::TowerEntity()
{

}

TowerEntity::~TowerEntity()
{
    delete m_cHealth;
    delete m_cWeapon;
}

void TowerEntity::update(){

}

void TowerEntity::save(QFile *file)
{

}

void TowerEntity::load(string &line)
{
    int pos;
    BaseEntity::load(line);
    TowerEntity::health = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    TowerEntity::damage = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    TowerEntity::cooldown = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    Model::instance()->addEntity(this);
    cout << "loaded COMPONENT-ENTITY" << endl;
}

//runs primary action of the entity
ComponentEntity::ComponentEntity()
{

}

void ComponentEntity::load(string &line){
    int pos;
    ComponentEntity::load(line);
    type = line.substr(0, pos = line.find(","));
    Model::instance()->addEntity(this);
    cout << "loaded COMPONENT-ENTITY" << endl;
}

void ComponentEntity::primaryAction(int x, int y) {

if(Model::instance()->createTower(x,y)) Model::instance()->killEntity(id);
}
