#include "objectlabel.h"

ObjectLabel::ObjectLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : QLabel(parent), win(window), data(data)
{
    //set the ObjectLabels graphic
    setPixmap(image.pixmap(size()));
}

ObjectLabel::~ObjectLabel()
{
    delete win;
}
