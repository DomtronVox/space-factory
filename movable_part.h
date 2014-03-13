#include <string>

#include "base_enity.h"

#ifndef MOVABLE_PART_H
#define MOVABLE_PART_H

class MovablePart {

    int speed;
    int x_target;
    int y_target;
    bool moving;

  public:
    MovablePart(int initSpeed)
        : speed(initSpeed), moving(true)
    {}

    MovablePart(int initSpeed, int initx_target, int inity_target)
        : speed(initSpeed), x_target(initx_target), y_target(inity_target), moving(false)
    {}

    //changes movment target
    void moveTo(int x, int y);

    //tells the part a tick has passed.
    void tick(BaseEntity *master);

    //convert the entity to a string so it can be saved
    string serialise();
};

#endif // MOVABLE_PART_H
