#ifndef MOVABLE_PART_H
#define MOVABLE_PART_H

#include <string>

#include "base_entity.h"

class MovablePart {
    int speed;
    int x_target;
    int y_target;
    bool moving;

  public:
    MovablePart(int initSpeed, int x_target, int y_target)
        : speed(initSpeed), x_target(x_target), y_target(y_target), moving(true)
    {}

    MovablePart(string &line);

    //convert the entity to a string so it can be saved
    string stringify() {
        return to_string(speed) + "," + to_string(x_target) + "," + to_string(y_target) + "," + to_string(moving);
    }

    //returns weather the part is moving
    bool getMoving(){ return moving; }

    //toggles weather the part is moving or not.
    void toggleMoving();

    //changes movment target
    void moveTo(int x, int y);

    //tells the part a tick has passed.
    void tick(BaseEntity *master);
};

#endif // MOVABLE_PART_H
