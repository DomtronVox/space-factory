#include <string>
#include <fstream>


#ifndef BASE_ENITY_H
#define BASE_ENITY_H

#include <QString>
using namespace std;

//Basic game entity holds position and entity image
class BaseEntity{

protected:
    string owner;
    int id, x, y;
    string image;

public:


    BaseEntity(int initId, string owner, int initX, int initY, string initImage)
        : id(initId), owner(owner), x(initX), y(initY), image(initImage)
    {}

    BaseEntity(ifstream *file);
    virtual ~BaseEntity() {  }

    //returns a string that describes the entity
    virtual string stringify(){
        return to_string(id)+","+to_string(x)+","+to_string(y)+","+image;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getId(){ return id; }
    string getImage() { return image; }
    string getOwner() { return owner; }

    //moves the object to the given position
    void move(int newx, int newy) { x=newx; y=newy; }

    virtual void update() {}

    //serialize and write the entity data to the file
    virtual void save(ofstream *file) {}
    //initilize the entity from a saved file
    virtual void load(ifstream *file) {}

    //runs primary action of the entity
    //TODO: When implementing multiplayer we should add owner the this prototype
    virtual void primaryAction(int x, int y) {}

    //damage the entity
    //TODO: This is a workaround so weapon part can hit entities.
    virtual void hit(int damage) {}
};


#endif // BASE_ENITY_H
