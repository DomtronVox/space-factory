#include "killable_part.h"

#include "model.h"

void KillablePart::hit(int damage) {

    curHealth = curHealth - damage;

    if (curHealth <= 0)
         Model::instance()->killEntity(id);
}
