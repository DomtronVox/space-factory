#include <string>
#ifndef BUILD_PART_H
#define BUILD_PART_H

using namespace std;

class BuilderPart{

    //holds the value curCooldown is set to after it reaches zero.
    const static int maxCooldown = 500; //TODO: couldn't think of a better name.
    //holds the weapons current cooldown count before it can fire again.
    int curCooldown;
    //what the factory is building now
    char* target;

  public:
    //new builder part
    BuilderPart(char* initTarget)
        : target(initTarget), curCooldown(maxCooldown)
    {}

    //reinisilised builder part
    BuilderPart(char* initTarget, int initCurCooldown)
        : target(initTarget), curCooldown(initCurCooldown)
    {}

    ~BuilderPart(){ }

    //tells the part a tick has passed. if countdown is zero this returns true otherwise it returns false.
    //  takes the base entities position
    void tick(int x, int y);

    //convert the entity to a string so it can be saved
    string serialise();

    //creates a new component entity
    void build_component(int x,int y);
};

#endif // BUILD_PART_H
