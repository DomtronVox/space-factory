#ifndef WEAPON_PART_H
#define WEAPON_PART_H

#include <string>

#include "base_entity.h"
#include "killable_part.h"

using namespace std;

class WeaponPart {

    int damage;      //amount of damage returned by fire()
    int range;       //distance the weapon can reach with it's fire
    int maxCooldown; //holds the value curCooldown is set to after fire() is called.
    int curCooldown; //holds the weapons current cooldown count before it can fire again.
    int target_id;   //


public:
    //new weapon part
    WeaponPart(int damage, int range, int cooldown)
        :damage(damage), range(range), maxCooldown(cooldown), curCooldown(cooldown), target_id(-1)
    {}

    //reinisilizes weapon part
    WeaponPart(int damage, int range, int maxCooldown, int curCooldown)
        :damage(damage), range(range), maxCooldown(maxCooldown), curCooldown(curCooldown), target_id(-1)
    {}

    bool hasTarget();
    int getTargetX();
    int getTargetY();

    //tells the part a tick has passed. Cools weapon down.
    void tick(string owner, int x, int y);

    //convert the entity to a string so it can be saved
    string serialise();

};

#endif // WEAPON_PART_H
