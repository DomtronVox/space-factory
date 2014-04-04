#include "angular_part.h"

void AngularPart::turnToPoint(BaseEntity* master, int x, int y){
    target_angle = (atan2(y-master->getY(), x-master->getX()) * 180) / 3.141592653589793;
}


void AngularPart::tick(BaseEntity* master){
    if (weapon->hasTarget())
        turnToPoint(master, weapon->getTargetX(), weapon->getTargetY());

    if (master->getAngle() > target_angle-2) {
        master->setAngle(master->getAngle() - speed);

        //make sure we don't overshoot the target
        if (master->getAngle() < target_angle+2)
            master->setAngle(target_angle);

    } else if (master->getAngle() < target_angle+2) {
        master->setAngle(master->getAngle() + speed);

        //make sure we don't overshoot the target
        if (master->getAngle() > target_angle-2)
            master->setAngle(target_angle);
    }
}
