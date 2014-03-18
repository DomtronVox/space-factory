#include <vector>

#include "weapon_part.h"

#include "model.h"

bool WeaponPart::hasTarget(){
    if (target == NULL ) return false;
    else                 return true;
}


void WeaponPart::tick(string owner, int x, int y) {

    //cool down weapon
    if (curCooldown > 0) {
        curCooldown--;

    //if a target has been aquired check it then fire.
    } else if (target != NULL){
        //make sure target is still in range
        //TODO: this should probebly be handled by another function so it can be expanded to things other then circles
        if( pow(target->getX()-x, 2) + pow(target->getY()-y, 2) > pow(range, 2) ){
            target = NULL;

        //fire weapon
        } else {
            curCooldown = maxCooldown;
            target->hit(damage);
        }

    //if we have no target try to get one
    } else {
        vector<BaseEntity*> in_range = Model::instance()->getInArea(x,y, range);
        for (unsigned int i = 0; i < in_range.size(); ++i) {
            if (in_range.at(i)->getOwner() != owner) {
                target = in_range.at(i);
            }
        }
    }

}
