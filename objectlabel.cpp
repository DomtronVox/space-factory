#include "objectlabel.h"

ObjectLabel::ObjectLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : QLabel(parent), win(window), data(data)
{
    //set the ObjectLabels graphic
    setPixmap(image.pixmap(size()));

    convertToScreenCoords();
}

ObjectLabel::~ObjectLabel()
{
    delete win;
}

//converts the position given by the data model entity to a screen position.
//  I.e. the center of the screen should be (0,0)
void ObjectLabel::convertToScreenCoords(){
    //convert and set coordinates
    this->setGeometry(
                data->getX() + (win->size().width()/2),
                data->getY() + (win->size().height()/2),
                width(), height());
}
