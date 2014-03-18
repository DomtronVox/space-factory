#include <string>

#include "base_entity.h"

#ifndef MOVABLE_PART_H
#define MOVABLE_PART_H

class MovablePart {
    int id;
    int speed;
    int x_target;
    int y_target;
    bool moving;

  public:
    MovablePart(int initSpeed)
        : speed(initSpeed), moving(true)
    {}

    MovablePart(int initSpeed, int initx_target, int inity_target, int initid)
        : speed(initSpeed), x_target(initx_target), y_target(inity_target),
          moving(true), id(initid)
    {}

    //returns weather the part is moving
    bool getMoving(){ return moving; }

    //toggles weather the part is moving or not.
    void toggleMoving();

    //changes movment target
    void moveTo(int x, int y);

    //tells the part a tick has passed.
    void tick(BaseEntity *master);

    //convert the entity to a string so it can be saved
    string serialise();
};

#endif // MOVABLE_PART_H
