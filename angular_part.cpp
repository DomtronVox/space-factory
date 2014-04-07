#include "angular_part.h"

#include <iostream>

AngularPart::AngularPart(WeaponPart *weapon, string &line) : weapon(weapon) {
    int pos;

    target_angle = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    speed = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
}

void AngularPart::turnToPoint(BaseEntity* master, int x, int y){
    target_angle = (atan2(y-master->getY(), x-master->getX()) * 180) / 3.141592653589793;

    if (target_angle < 0)
        target_angle = (target_angle % 360) + 360;
    else
        target_angle = target_angle % 360;
}


void AngularPart::tick(BaseEntity* master){
    if (weapon->hasTarget()) {
        turnToPoint(master, weapon->getTargetX(), weapon->getTargetY());
    }

    int my_angle = master->getAngle();

    //find the distance that must be traveled both clock- and counter clock- wise
    int clockwise_dist, counterwise_dist;
    if (target_angle > my_angle) {
        clockwise_dist = target_angle - my_angle;
        counterwise_dist = 360 - clockwise_dist;
    } else {
        counterwise_dist = my_angle - target_angle;
        clockwise_dist = 360 - counterwise_dist;
    }

    //alter the entity's angle
    //If either is zero we don't need to move
    if (clockwise_dist == 0 || counterwise_dist == 0){
        return;

    //move in the clockwise direction
    } else if (clockwise_dist < counterwise_dist) {
        //make sure we don't overshoot the target
        if (clockwise_dist < speed) {
            master->setAngle(target_angle);
        } else {
            master->setAngle(my_angle + speed);
        }

    //move in the counter clockwise direction
    } else {
        //make sure we don't overshoot the target
        if (counterwise_dist < speed) {
            master->setAngle(target_angle);
        } else {
            master->setAngle(my_angle - speed);
        }
    }
}
