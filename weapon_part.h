#ifndef WEAPON_PART_H
#define WEAPON_PART_H

using namespace std;

class WeaponPart {

    int cooldown;
    int damage;

  public:
    //returns int > 0 if the weapon can fire otherwise it returns 0.
    int fire();

    //tells the part a tick has passed. Cools weapon down.
    void update();

};

#endif // WEAPON_PART_H
