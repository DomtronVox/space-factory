#ifndef WEAPON_PART_H
#define WEAPON_PART_H

#include <string>

#include "base_entity.h"
#include "killable_part.h"

using namespace std;

class WeaponPart {

    //amount of damage returned by fire()
    int damage;
    //distance the weapon can reach with it's fire
    int range;
    //holds the value curCooldown is set to after fire() is called.
    int maxCooldown; //TODO: couldn't think of a better name.
    //holds the weapons current cooldown count before it can fire again.
    int curCooldown;

    int target_id;


  public:
    //new weapon part
    WeaponPart(int damage, int range, int cooldown)
        :damage(damage), range(range), maxCooldown(cooldown), curCooldown(cooldown), target_id(-1)
    {}

    //reinisilizes weapon part
    WeaponPart(string &line);

    //convert the entity to a string so it can be saved
    string stringify() {
        return to_string(damage) + "," + to_string(range) + "," + to_string(maxCooldown) + "," + to_string(curCooldown) + "," + to_string(target_id);
    }

    bool hasTarget();
    int getTargetX();
    int getTargetY();

    //tells the part a tick has passed. Cools weapon down.
    void tick(string owner, int x, int y);

};

#endif // WEAPON_PART_H
