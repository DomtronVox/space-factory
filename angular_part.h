#ifndef ANGULARPART_H
#define ANGULARPART_H

#include "base_entity.h"

using namespace std;

//allows the entity to rotateclass AngularPart {
class AngularPart {
    double target_angle;
    int speed; //how many degrees the entity can turn in a tick

  public:
    AngularPart(int targetAngle, int speed) : target_angle(targetAngle), speed(speed) {}

    //changes the angle to point to a point.
    void turnToPoint(BaseEntity* master, int x, int y);


    //tells the part a tick has passed.
    void update(BaseEntity* master);


};


#endif // ANGULARPART_H
