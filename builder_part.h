#include <string>

#ifndef BUILD_PART_H
#define BUILD_PART_H

class BuilderPart{

    int countdown;
    string target;

  public:
    BuilderPart(string initTarget, int initCountdown) : target(initTarget), countdown(initCountdown) {}

    //tells the part a tick has passed. Cools weapon down.
    void update();

};

#endif // BUILD_PART_H
