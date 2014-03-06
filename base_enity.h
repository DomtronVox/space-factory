#include <string>

#ifndef BASE_ENITY_H
#define BASE_ENITY_H

using namespace std;

//Basic game entity holds position and entity image
class BaseEntity{

    int x, y;
    string image;

  public:
    BaseEntity(int, int, string);
    virtual void update();

};


#endif // BASE_ENITY_H
