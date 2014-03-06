#include <QTimer>

#ifndef MODEL_H
#define MODEL_H

Class Map;

class Model {
 //singleton design
 //variables
    int * highscores;
    int current;
    Map* map;
};

//functions
class HighScore {
//variables
    string filename; //should we have this be a file object?
    vector<string> names;
    vector<int> scores;

//functions
    constructor(filename);
    destructor();
    save();
};

class Map {
//variables
    static id = 0;
    vector<PosEntity> entities;

//functions
    create entity(owner, type, pos);
    kill entity(id);
    update();
};

class Angular {
//variables
    int angle;

//functions
    turnToPoint(x,y);
    checkAngle();
};


class Health {
//variables
    int maxHealth;
    int curHealth;

//functions
    hit();
    die();
};


class Weapon {
//variables
    QTimer cooldown;
    int damage;

//functions

};

#endif // MODEL_H
