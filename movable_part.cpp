#include "base_entity.h"
#include "movable_part.h"

void MovablePart::toggleMoving(){
    if (moving) moving = false;
    else        moving = true;
}


void MovablePart::tick(BaseEntity *master){

    //if moving variable is false don't move
    if (!moving) return;

    //get direction of target with relation to current position
    int x_dir = 0;
    int y_dir = 0;

    if (master->getX() > x_target) x_dir = -1;
    else if (master->getX() < x_target) x_dir = 1;

    if (master->getY() > y_target) y_dir = -1;
    else if (master->getY() < y_target) y_dir = 1;

    //move in the direction of the target position
    if (x_dir == y_dir && x_dir == 0){
      moving = false;

    } else if (abs(x_dir) == abs(y_dir)){
        master->move(master->getX()+x_dir*(speed/2),
                     master->getY()+y_dir*(speed/2));
    } else if (x_dir == 0){
        master->move(master->getX(),
                     master->getY()+y_dir*speed);
    } else if (y_dir == 0) {
        master->move(master->getX()+x_dir*speed,
                     master->getY());
    }
}
