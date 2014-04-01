#include "objectlabel.h"

#include "model.h"

ObjectLabel::ObjectLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image)
    : QLabel(parent), win(window), data_id(data->getId()), data(data)
{
    //set the ObjectLabels graphic
    setScaledContents(true);
    originalImage = image.pixmap(image.actualSize(win->size()/6));
    setPixmap(originalImage);
    this->setGeometry(x(), y(), image.actualSize(win->size()).width()/4, image.actualSize(win->size()).height()/4);

    updateData();

    //setup mouse tracking so we can handle click events on objects.
    setMouseTracking(true);
}

//converts the given position to a screen position.
//  I.e. given (0,0) should return the point at the center of the screen
QPoint ObjectLabel::convertToScreenCoords(QPoint pos){
    return QPoint( //convert given coordinates
      ( pos.x() + (win->size().width()/2)),
      (-pos.y() + (win->size().height()/2))
    );
}

//converts the given position a model position.
//  I.e. given the center of the screen the return should be (0,0)
QPoint ObjectLabel::convertToModelCoords(QPoint pos){
    return QPoint( //convert given coordinates
      ( pos.x() - (win->size().width()/2)),
      -(pos.y() - (win->size().height()/2))
    );
}


void ObjectLabel::updateData(){
    if (Model::instance()->getById(data_id) == NULL) {
        deleteLater();
    } else {
        //setup a rect describing the lables position
        QRect location = QRect(pos(), size());
        location.moveCenter(convertToScreenCoords(QPoint(data->getX(), data->getY())));

        //set location
        setGeometry(location);

        //setup a matric describing the images rotation
        QPixmap image = QPixmap(originalImage);
        QTransform rt;
        rt.rotate(data->getAngle());
        setPixmap(image.transformed(rt));
    }
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
    if (mouseDragging) {
        //move the model entity to the new position
        QPoint new_pos = convertToModelCoords( pos() + (ev->pos() - this->offset) );
        data->move(new_pos.x(), new_pos.y());
    }
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

        data->primaryAction(data->getX(), data->getY());
   }
}
