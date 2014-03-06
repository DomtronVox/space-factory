#ifndef ANGULARPART_H
#define ANGULARPART_H

//allows the entity to rotate
class AngularPart {

    double curAngle;
    double targetAngle;
    int speed; //how many degrees the entity can turn in a tick

    //varifies the angle is in the proper range.
    void checkAngle();

  public:
    AngularPart(int initAngle) : curAngle(initAngle) {}

    //changes the angle to point to a point.
    void turnToPoint(int my_x, my_y, x,y);


    //tells the part a tick has passed.
    void update();


};


#endif // ANGULARPART_H
