#ifndef KILLABLE_PART_H
#define KILLABLE_PART_H

#include <string>

using namespace std;

//holds data that allows entities to be destroyed
class KillablePart {
    int id;
    int maxHealth;
    int curHealth;
    bool invincible;

    void checkInvincible();

public:
    //brand new killable part
    KillablePart(int id, int initMax)
        : id(id), maxHealth(initMax), curHealth(initMax)
    { checkInvincible(); }

    //reinisilized killable part.
    KillablePart(int id, string &line);

    //convert the entity to a string so it can be saved
    string stringify() {
        return to_string(maxHealth) + "," + to_string(curHealth);
    }

    //call this function each time an entity is hit. returns true if the entity should die.
    void hit(int damage);
};

#endif // KILLABLE_PART_H
