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
ShipEntity::ShipEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(id,owner,x,y,image)
{
    ShipEntity::health = health;
    ShipEntity::damage = damage;
    ShipEntity::cooldown = cooldown;
    m_cHealth = new KillablePart(id, health);
    m_cWeapon = new WeaponPart(damage, Model::settings.ship_range, cooldown);
    m_cMoveable = new MovablePart(Model::settings.ship_speed, 0, 0);
    m_cAngular = new AngularPart(0, Model::settings.ship_speed, m_cWeapon);
    m_cAngular->turnToPoint(this, 0,0);
}

ShipEntity::ShipEntity()
{

}

ShipEntity::~ShipEntity()
{
    delete m_cHealth;
    delete m_cWeapon;
    delete m_cMoveable;
    delete m_cAngular;
}

void ShipEntity::update()
{
    m_cMoveable->tick(this);
    m_cWeapon->tick(getOwner(), getX(), getY());
    m_cAngular->tick(this);

    //the moving bool should be oppisite the hasTarget bool so the entity is either moving or attacking.
    if( m_cMoveable->getMoving() == m_cWeapon->hasTarget() )
        m_cMoveable->toggleMoving();
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
     m_cHealth = new KillablePart(id, health);
     m_cWeapon = new WeaponPart(damage, Model::settings.ship_range, cooldown);
     m_cMoveable = new MovablePart(Model::settings.ship_speed, 0, 0);
     Model::instance()->addEntity(this);
     cout << "loaded SHIP-ENTITY" << endl;

}

//factory functions
FactoryEntity::FactoryEntity(int id, string owner, int x, int y, string image, int health, int damage) : BaseEntity(id,owner,x,y,image)
{
    FactoryEntity::health = health;
    FactoryEntity::damage = damage;
    m_cHealth = new KillablePart(id, health);
    m_cBulder = new BuilderPart(Model::settings.factory_target, Model::settings.factory_counter);

}

FactoryEntity::FactoryEntity()
{
    m_cHealth = new KillablePart(id, health);
    m_cBulder = new BuilderPart(Model::settings.factory_target, Model::settings.factory_counter);
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
TowerEntity::TowerEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(id,owner,x,y,image)
{
    TowerEntity::health = health;
    TowerEntity::damage = damage;
    TowerEntity::cooldown = cooldown;
    m_cHealth = new KillablePart(id, health);
    m_cWeapon = new WeaponPart(damage, Model::settings.tower_range, cooldown);
    m_cAngular = new AngularPart(0, Model::settings.ship_speed, m_cWeapon);
}

TowerEntity::TowerEntity()
{

}

TowerEntity::~TowerEntity()
{
    delete m_cHealth;
    delete m_cWeapon;
    delete m_cAngular;
}

void TowerEntity::update(){

    m_cWeapon->tick(getOwner(), getX(), getY());
    m_cAngular->tick(this);
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
    m_cHealth = new KillablePart(id, health);
    m_cWeapon = new WeaponPart(damage, Model::settings.tower_range, cooldown);
    Model::instance()->addEntity(this);
    cout << "loaded COMPONENT-ENTITY" << endl;
}

//runs primary action of the entity
ComponentEntity::ComponentEntity()
{

}

void ComponentEntity::load(string &line){
    int pos;
    BaseEntity::load(line);
    type = line.substr(0, pos = line.find(","));
    Model::instance()->addEntity(this);
    cout << "loaded COMPONENT-ENTITY" << endl;
}

void ComponentEntity::primaryAction(int x, int y) {

    if(Model::instance()->createTower(x,y))
        Model::instance()->killEntity(id);
}
