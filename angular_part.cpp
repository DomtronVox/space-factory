#include "angular_part.h"

void AngularPart::turnToPoint(BaseEntity* master, int x, int y){
    target_angle = (atan2(y-master->getY(), x-master->getX()) * 180) / 3.141592653589793;
}


void AngularPart::update(BaseEntity* master){
    if (master->getAngle() > target_angle-2) {
        master->setAngle(master->getAngle() + speed);
    } else if (master->getAngle() < target_angle+2) {
        master->setAngle(master->getAngle() - speed);
    }
}
