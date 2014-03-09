#include <string>

#include "entities.h"

//part includes
#include "angular_part.h"
#include "killable_part.h"
#include "weapon_part.h"
#include "builder_part.h"


//ship functions
void ShipEntity::update(){

}

//factory functions
void FactoryEntity::update(){
    m_cBulder->tick(x,y);
}

//tower functions
void TowerEntity::update(){

}
