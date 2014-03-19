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

    BaseEntity *target;


  public:
    //new weapon part
    WeaponPart(int damage, int range, int cooldown)
        :damage(damage), range(range), maxCooldown(cooldown), curCooldown(cooldown), target(NULL)
    {}

    //reinisilizes weapon part
    WeaponPart(int damage, int range, int maxCooldown, int curCooldown)
        :damage(damage), range(range), maxCooldown(maxCooldown), curCooldown(curCooldown), target(NULL)
    {}

    bool hasTarget();

    //tells the part a tick has passed. Cools weapon down.
    void tick(string owner, int x, int y);

    //convert the entity to a string so it can be saved
    string serialise();

};

#endif // WEAPON_PART_H
