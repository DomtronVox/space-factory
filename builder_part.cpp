#include <string>

#include "builder_part.h"

#include "model.h"


BuilderPart::BuilderPart(string &line){
    int pos;

    target = line.substr(0, pos = line.find(","));
    line.erase(0, pos + 1);
    maxCooldown = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
    curCooldown = stoi(line.substr(0, pos = line.find(",")));
    line.erase(0, pos + 1);
}

//tells the part a tick has passed. if countdown is zero this returns true otherwise it returns false.
void BuilderPart::tick(int x, int y){
    curCooldown--;
    if (curCooldown <= 0){
        curCooldown = maxCooldown;
        build_component(x,y);
    }
}

void BuilderPart::build_component(int x, int y){

    //randomize a position near the bulder object
    int offset_x = rand() % 40 - 10;
    int offset_y = rand() % 40 - 10;

    //create the compenent
    Model::instance()->createComponent("repair_component", target, offset_x+x,offset_y+y);
}

