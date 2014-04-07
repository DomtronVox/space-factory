#include <string>
#include <QTextStream>
#include <QDebug>
#include "entities.h"

#include "movable_part.h"
#include "angular_part.h"
#include "killable_part.h"
#include "weapon_part.h"
#include "builder_part.h"

//TODO: change code that needs model and remove this include
#include "model.h"



//#########################
//#### Ship Functions #####
//#########################
ShipEntity::ShipEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(id,owner,x,y,image) {
    m_cHealth = new KillablePart(id, health);
    m_cWeapon = new WeaponPart(damage, Model::settings.ship_range, cooldown);
    m_cMoveable = new MovablePart(Model::settings.ship_speed, 0, 0);
    m_cAngular = new AngularPart(0, Model::settings.ship_speed, m_cWeapon);
    m_cAngular->turnToPoint(this, 0,0);
}


ShipEntity::ShipEntity(string &line) {
     BaseEntity::load(line);

     m_cHealth = new KillablePart(this->id, line);
     m_cWeapon = new WeaponPart(line);
     m_cMoveable = new MovablePart(line);
     m_cAngular = new AngularPart(m_cWeapon, line);
}

ShipEntity::~ShipEntity() {
    delete m_cHealth;
    delete m_cWeapon;
    delete m_cMoveable;
    delete m_cAngular;
}


void ShipEntity::update() {
    m_cMoveable->tick(this);
    m_cWeapon->tick(getOwner(), getX(), getY());
    m_cAngular->tick(this);

    //the moving bool should be oppisite the hasTarget bool so the entity is either moving or attacking.
    if( m_cMoveable->getMoving() == m_cWeapon->hasTarget() )
        m_cMoveable->toggleMoving();
}






//###########################
//#### Factory Functions ####
//###########################


//factory functions
FactoryEntity::FactoryEntity(int id, string owner, int x, int y, string image, int health) : BaseEntity(id,owner,x,y,image) {
    m_cHealth = new KillablePart(id, health);
    m_cBulder = new BuilderPart(Model::settings.factory_target, Model::settings.factory_counter);
}


FactoryEntity::FactoryEntity(string &line) {
    BaseEntity::load(line);

    m_cHealth = new KillablePart(this->id, line);
    m_cBulder = new BuilderPart(line);
}

FactoryEntity::~FactoryEntity() {
    delete m_cHealth;
    delete m_cBulder;
}

void FactoryEntity::update() {
    m_cBulder->tick(x,y);
}





//#########################
//#### Tower Functions ####
//#########################

TowerEntity::TowerEntity(int id, string owner, int x, int y, string image, int health, int damage, int cooldown) : BaseEntity(id,owner,x,y,image) {
    m_cHealth = new KillablePart(id, health);
    m_cWeapon = new WeaponPart(damage, Model::settings.tower_range, cooldown);
    m_cAngular = new AngularPart(0, Model::settings.ship_speed, m_cWeapon);
}


TowerEntity::TowerEntity(string &line) {
    BaseEntity::load(line);

    m_cHealth = new KillablePart(id, line);
    m_cWeapon = new WeaponPart(line);
    m_cAngular = new AngularPart(m_cWeapon, line);
}

TowerEntity::~TowerEntity() {
    delete m_cHealth;
    delete m_cWeapon;
    delete m_cAngular;
}

void TowerEntity::update(){
    m_cWeapon->tick(getOwner(), getX(), getY());
    m_cAngular->tick(this);
}





//#############################
//#### Component Functions ####
//#############################

ComponentEntity::ComponentEntity(string &line) {
    BaseEntity::load(line);

    int pos;
    type = line.substr(0, pos = line.find(","));
}

//runs primary action of the entity
void ComponentEntity::primaryAction(int x, int y) {
    if(Model::instance()->createTower(x,y))
        Model::instance()->killEntity(id);
}
