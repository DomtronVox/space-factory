#include <string>
#ifndef BUILD_PART_H
#define BUILD_PART_H

using namespace std;

class BuilderPart{

    //holds the value curCooldown is set to after it reaches zero.
    const static int maxCooldown = 4; //TODO: couldn't think of a better name.
    //holds the weapons current cooldown count before it can fire again.
    int curCooldown;
    //what the factory is building now
    string target;

  public:
    //new builder part
    BuilderPart(string initTarget)
        : target(initTarget), curCooldown(maxCooldown)
    {}

    //reinisilised builder part
    BuilderPart(string initTarget, int initCurCooldown)
        : target(initTarget), curCooldown(initCurCooldown)
    {}

    //tells the part a tick has passed. if countdown is zero this returns true otherwise it returns false.
    //  takes the base entities position
    bool tick(int x, int y);

    //convert the entity to a string so it can be saved
    string serialise();

    //creates a new component entity
    void build_component(int x,int y);
};

#endif // BUILD_PART_H
