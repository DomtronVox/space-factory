#ifndef OBJECTLABEL_H
#define OBJECTLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QIcon>

#include "game_window.h"

#include "base_enity.h"
#include "entities.h"

//forward declares gamewindow since it will include ObjectLable.h
class GameWindow;

//this is the visual portion of entities. It should support mouse clicking
class ObjectLabel : public QLabel
{

    GameWindow *win;
    BaseEntity *data;

    void convertToScreenCoords();

  public:
    ObjectLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image);
    ~ObjectLabel();

};

//this class is for components which can be dragged
class DraggableLabel : public ObjectLabel
{

    bool mouseDragging;
    QPoint offset;

  public:
    DraggableLabel(QWidget *parent, GameWindow *window, BaseEntity *data, QIcon image);

    //mouse events
    void mouseMoveEvent(QMouseEvent *ev) {};
    void mousePressEvent(QMouseEvent *ev) {};
    void mouseReleaseEvent(QMouseEvent *ev) {};

};

#endif // OBJECTLABEL_H
