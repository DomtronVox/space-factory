#include <string>
#include <fstream>

#ifndef BASE_ENITY_H
#define BASE_ENITY_H

using namespace std;

//Basic game entity holds position and entity image
class BaseEntity{

protected:
    int id, x, y;
    string image;

public:
    BaseEntity(int initId, int initX, int initY, string initImage)
        : id(initId), x(initX), y(initY), image(initImage)
    {}
    BaseEntity(ifstream *file);
    virtual ~BaseEntity() {}

    //returns a string that describes the entity
    virtual string stringify(){
        return "BaseEntity:"+to_string(id)+","+to_string(x)+","+to_string(y)+","+image;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getId(){ return id; }

    virtual void update() {}

    //serialize and write the entity data to the file
    virtual void save(ofstream *file) {}
    //initilize the entity from a saved file
    virtual void load(ifstream *file) {}
};


#endif // BASE_ENITY_H
