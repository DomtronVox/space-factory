#include <string>

#ifndef BASE_ENITY_H
#define BASE_ENITY_H

//Basic game entity holds position and entity image
class BaseEntity{

    int x, y;
    string image;

  public:
    BaseEntity(int, int, string);


};


#endif // BASE_ENITY_H
