#include "objectlabel.h"

ObjectLabel::ObjectLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : QLabel(parent), win(window), data(data)
{
    //set the ObjectLabels graphic
    setScaledContents(true);
    setPixmap(image.pixmap(image.actualSize(win->size()/6)));
    this->setGeometry(x(), y(), image.actualSize(win->size()).width()/4, image.actualSize(win->size()).height()/4);

    QRect location = QRect(pos(), size());
    //center label on models position
    location.moveCenter(convertToScreenCoords(QPoint(data->getX(), data->getY())));
    //set location
    setGeometry(location);

    //setup mouse tracking so we can handle click events on objects.
    setMouseTracking(true);
}

ObjectLabel::~ObjectLabel()
{
    delete win;
}

//converts the position given by the data model entity to a screen position.
//  I.e. the center of the screen should be (0,0)
QPoint ObjectLabel::convertToScreenCoords(QPoint pos){
    return QPoint( //convert given coordinates
      (pos.x() + (win->size().width()/2)),
      (pos.y() + (win->size().height()/2))
    );
}


DraggableLabel::DraggableLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : ObjectLabel(parent, window, data, image)
{
    mouseDragging = false;

    //make sure dragable labels are on top so they are allways visible
    this->raise();
}

//moves the label when the mouse moves
void DraggableLabel::mouseMoveEvent(QMouseEvent *ev)
{
    //move the label to the new location
    if (mouseDragging) move(mapToParent(ev->pos() - this->offset));
}

//starts dragging the label
void DraggableLabel::mousePressEvent(QMouseEvent *ev)
{
    mouseDragging = true;
    offset = ev->pos();
}

//stops dragging the label
void DraggableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (mouseDragging){
        mouseDragging = false;
        //create move command and run it
        QPoint pos = convertToScreenCoords(ev->pos() - this->offset);
        data->move(pos.x(), pos.y());
    }
}
