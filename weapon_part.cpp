#include <vector>

#include "weapon_part.h"
#include "model.h"

int WeaponPart::getTargetX() { return Model::instance()->getById(target_id)->getX(); }

int WeaponPart::getTargetY() { return Model::instance()->getById(target_id)->getY(); }

bool WeaponPart::hasTarget(){
    if (Model::instance()->getById(target_id) == NULL ){
        target_id = -1;
        return false;
    }

    else {
        return true;
    }
}

void WeaponPart::tick(string owner, int x, int y) {

    //cool down weapon
    if (curCooldown > 0) {
        curCooldown--;
    }

    else if (hasTarget()){    //if a target has been aquired check it then fire.
        BaseEntity *target = Model::instance()->getById(target_id);

        //make sure target is still in range
        //TODO: this should probably be handled by another function so it can be expanded to things other then circles
        if( pow(target->getX()-x, 2) + pow(target->getY()-y, 2) > pow(range, 2) ){
            target_id = -1;
        }

        else {
            curCooldown = maxCooldown;
            target->hit(damage);
        }
    }

    else {
        vector<BaseEntity*> in_range = Model::instance()->getInArea(x,y, range);
        for (unsigned int i = 0; i < in_range.size(); ++i) {
            if (in_range.at(i)->getOwner() != owner) {
                target_id = in_range.at(i)->getId();
            }
        }
    }
}
