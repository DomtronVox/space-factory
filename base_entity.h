#include <string>
#include <QFile>


#ifndef BASE_ENITY_H
#define BASE_ENITY_H

#include <QString>
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





    BaseEntity(QFile *file);
    BaseEntity() {}
    virtual ~BaseEntity() {  }

    //returns a string that describes the entity
    virtual string stringify(){
        return to_string(id)+","+to_string(x)+","+to_string(y)+","+image;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getId(){ return id; }
    string getImage() { return image; }

    //moves the object to the given position
    void move(int newx, int newy) { x=newx; y=newy; }

    virtual void update() {}

    //serialize and write the entity data to the file
    void save(QFile *file);
    //initilize the entity from a saved file
    void load(string &line);

    //runs primary action of the entity
    //TODO: When implementing multiplayer we should add owner the this prototype
    virtual void primaryAction(int x, int y) {};
};


#endif // BASE_ENITY_H
