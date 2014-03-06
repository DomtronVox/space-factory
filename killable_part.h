#ifndef KILLABLE_PART_H
#define KILLABLE_PART_H

using namespace std;

//holds data that allows entities to be destroyed
class KillablePart {

    int maxHealth;
    int curHealth;

  public:
    KillablePart(int initMax, int initCur)
        : maxHealth(initMax), curHealth(initCur) {}

    //call this function each time an entity is hit. returns true if the entity should die.
    bool hit(int damage);
    //call this function to kill the entity
    void die();
};

#endif // KILLABLE_PART_H
