#ifndef WEAPON_PART_H
#define WEAPON_PART_H

using namespace std;

class WeaponPart {

    //holds the value curCooldown is set to after fire() is called.
    int maxCooldown; //TODO: couldn't think of a better name.
    //holds the weapons current cooldown count before it can fire again.
    int curCooldown;
    //amount of damage returned by fire()
    int damage;

  public:
    //new weapon part
    WeaponPart(int damage, int cooldown)
        :maxCooldown(cooldown), curCooldown(cooldown)
    {}

    //reinisilizes weapon part
    WeaponPart(int damage, int maxCooldown, int curCooldown)
        :maxCooldown(maxCooldown), curCooldown(curCooldown)
    {}

    //returns int > 0 if the weapon can fire otherwise it returns 0.
    int fire();

    //tells the part a tick has passed. Cools weapon down.
    void update();

    //convert the entity to a string so it can be saved
    string serialise();

};

#endif // WEAPON_PART_H
