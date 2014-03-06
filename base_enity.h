#include <string>
#include <fstream>

#ifndef BASE_ENITY_H
#define BASE_ENITY_H

using namespace std;

//Basic game entity holds position and entity image
class BaseEntity{

    int x, y;
    string image;

  public:
    BaseEntity(int, int, string);
    BaseEntity(ifstream *file);
    ~BaseEntity();

    virtual void update();

    //serialize and write the entity data to the file
    virtual void save(ofstream *file);
    //initilize the entity from a saved file
    virtual void load(ifstream *file);
};


#endif // BASE_ENITY_H
