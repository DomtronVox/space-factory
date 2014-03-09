#include <string>

#include "builder_part.h"

#include "model.h"


//tells the part a tick has passed. if countdown is zero this returns true otherwise it returns false.
bool BuilderPart::tick(int x, int y){
    curCooldown--;
    if (curCooldown <= 0){
        curCooldown = maxCooldown;
        build_component(x,y);
    }
}

void BuilderPart::build_component(int x, int y){

    //randomize a position near the bulder object
    int offset_x = random() % 10-8;
    int offset_y = random() % 10-8;

    //create the compenent
    Model::instance()->createComponent(target, offset_x+x,offset_y+y);
}

