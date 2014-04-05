#include "angular_part.h"
#include <iostream>

void AngularPart::turnToPoint(BaseEntity* master, int x, int y){
    target_angle = (atan2(y-master->getY(), x-master->getX()) * 180) / 3.141592653589793;

    if (target_angle < 0) target_angle = (target_angle % 360) + 360;
    else                  target_angle = target_angle % 360;
    std::cout << master->getId()<< ',' << target_angle << std::endl;
}


void AngularPart::tick(BaseEntity* master){
    if (weapon->hasTarget())
        turnToPoint(master, weapon->getTargetX(), weapon->getTargetY());
    std::cout << (master->getAngle() > target_angle) << endl;
    if (master->getAngle() > target_angle) {
        master->setAngle(master->getAngle() - speed);

        //make sure we don't overshoot the target
        if (master->getAngle() < target_angle)
            master->setAngle(target_angle);

    } else if (master->getAngle() < target_angle) {
        master->setAngle(master->getAngle() + speed);

        //make sure we don't overshoot the target
        if (master->getAngle() > target_angle)
            master->setAngle(target_angle);
    }
}
