#ifndef BASE_ENITY_H
#define BASE_ENITY_H

#include <string>
#include <QFile>
#include <QString>

using namespace std;

//Basic game entity holds position and entity image
class BaseEntity{

protected:
    int id;
    string owner;
    int x, y;
    int angle;
    string image;

public:
    BaseEntity(int initId, string owner, int initX, int initY, string initImage)
        : id(initId), owner(owner), x(initX), y(initY), angle(0), image(initImage)
    {}

    BaseEntity(QFile *file);
    BaseEntity() {}
    virtual ~BaseEntity() {  }

    //returns a string that describes the entity
    virtual string stringify(){
        return to_string(id)+","+owner+","+to_string(x)+","+to_string(y)+","+to_string(angle)+","+image;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getAngle() { return angle % 360; }
    int getId(){ return id; }
    string getImage() { return image; }
    string getOwner() { return owner; }

    void setAngle(int angle) { this->angle = angle; }

    //moves the object to the given position
    void move(int newx, int newy) { x=newx; y=newy; }

    virtual void update() {}

    //serialize and write the entity data to the file
    void save(QFile *file);
    //initilize the entity from a saved file
    void load(string &line);

    //runs primary action of the entity
    virtual void primaryAction(int /*x*/, int /*y*/) { }

    //damage the entity
    //TODO: This is a workaround so weapon part can hit entities.
    virtual void hit(int /*damage*/) {}
};


#endif // BASE_ENITY_H
