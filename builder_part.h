#include <string>
#ifndef BUILD_PART_H
#define BUILD_PART_H

using namespace std;

class BuilderPart{

    //what the factory is building now
    string target;
    //holds the value curCooldown is set to after it reaches zero.
    int maxCooldown;
    //holds the weapons current cooldown count before it can fire again.
    int curCooldown;


  public:
    //new builder part
    BuilderPart(string initTarget, int maxCooldown)
        : target(initTarget), maxCooldown(maxCooldown), curCooldown(maxCooldown)
    {}

    //reinisilised builder part
    BuilderPart(string &line);

    //convert the entity to a string so it can be saved
    string stringify(){
        return target + "," + to_string(maxCooldown) + "," + to_string(curCooldown);
    }


    //tells the part a tick has passed. if countdown is zero this returns true otherwise it returns false.
    //  takes the base entities position
    void tick(int x, int y);

    //creates a new component entity
    void build_component(int x,int y);
};

#endif // BUILD_PART_H
