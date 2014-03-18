#include <string>
#ifndef BUILD_PART_H
#define BUILD_PART_H

using namespace std;

class BuilderPart{

    //holds the value curCooldown is set to after it reaches zero.
    //TODO: couldn't think of a better name and the hard coded value needs moving to a central location.
    const static int maxCooldown = 50;
    //what the factory is building now
    char* target;
    //holds the weapons current cooldown count before it can fire again.
    int curCooldown;


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
