#include <string>

#ifndef KILLABLE_PART_H
#define KILLABLE_PART_H

using namespace std;

//holds data that allows entities to be destroyed
class KillablePart {
    int id;
    int maxHealth;
    int curHealth;

  public:
    //brand new killable part
    KillablePart(int id, int initHealth)
        : id(id), maxHealth(initHealth), curHealth(initHealth) {}

    //reinisilized killable part.
    KillablePart(int id, int initMax, int initCur)
        : id(id), maxHealth(initMax), curHealth(initCur) {}

    //call this function each time an entity is hit. returns true if the entity should die.
    void hit(int damage);

    //convert the entity to a string so it can be saved
    string serialise();
};

#endif // KILLABLE_PART_H
