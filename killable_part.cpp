#include "killable_part.h"
#include "model.h"

void KillablePart::checkInvincible() {
    if (maxHealth == 0) invincible = true;
    else                invincible = false;
}


KillablePart::KillablePart(int id, string &line) : id(id) {
    int pos;

    maxHealth = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    curHealth = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);

    checkInvincible();
}

void KillablePart::hit(int damage) {
    curHealth = curHealth - damage;
    if (curHealth <= 0 && !invincible)
         Model::instance()->killEntity(id);
}
