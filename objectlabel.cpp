#include "objectlabel.h"

ObjectLabel::ObjectLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : QLabel(parent), win(window), data(data)
{
    //set the ObjectLabels graphic
    setPixmap(image.pixmap(image.actualSize(win->size()/6)));
    this->setGeometry(x(), y(), image.actualSize(win->size()).width()/4, image.actualSize(win->size()).height()/4);

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
                (data->getX() + (win->size().width()/2)) - (this->pixmap()->width()/2),
                (data->getY() + (win->size().height()/2)) - (this->pixmap()->height()/2),
                width(), height());
}


DraggableLabel::DraggableLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : ObjectLabel(parent, window, data, image)
{
    //make sure dragable labels are on top so they are allways visible
    this->raise();
}

