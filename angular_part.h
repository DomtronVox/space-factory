#ifndef ANGULARPART_H
#define ANGULARPART_H

#include "base_entity.h"
#include "weapon_part.h"

using namespace std;

//allows the entity to rotateclass AngularPart {
class AngularPart {
    int target_angle;
    int speed; //how many degrees the entity can turn in a tick

    WeaponPart * weapon; //TODO: This is hacky and should be handled a different way.

  public:
    AngularPart(int targetAngle, int speed, WeaponPart *weapon) : target_angle(targetAngle), speed(speed), weapon(weapon) {}

    //reinisilised angular part
    AngularPart(WeaponPart *weapon, string &line);

    //convert the entity to a string so it can be saved
    string stringify() {
        return to_string(target_angle) + "," + to_string(speed);
    }

    //changes the angle to point to a point.
    void turnToPoint(BaseEntity* master, int x, int y);

    //tells the part a tick has passed.
    void tick(BaseEntity* master);
};


#endif // ANGULARPART_H
