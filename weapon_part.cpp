#include <vector>

#include "weapon_part.h"

#include "model.h"

WeaponPart::WeaponPart(string &line) {
    int pos;

    damage = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    range = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    maxCooldown = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    curCooldown = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    target_id = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
}


int WeaponPart::getTargetX() { return Model::instance()->getById(target_id)->getX(); }

int WeaponPart::getTargetY() { return Model::instance()->getById(target_id)->getY(); }

bool WeaponPart::hasTarget(){
    if (Model::instance()->getById(target_id) == NULL ){
        target_id = -1;
        return false;

    } else {
        return true;
    }
}


void WeaponPart::tick(string owner, int x, int y) {

    //cool down weapon
    if (curCooldown > 0) {
        curCooldown--;

    //if a target has been aquired check it then fire.
    } else if (hasTarget()){
        BaseEntity *target = Model::instance()->getById(target_id);

        //make sure target is still in range
        //TODO: this should probebly be handled by another function so it can be expanded to things other then circles
        if( pow(target->getX()-x, 2) + pow(target->getY()-y, 2) > pow(range, 2) ){
            target_id = -1;

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
                target_id = in_range.at(i)->getId();
            }
        }
    }

}
