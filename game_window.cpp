#include <QTimer>
#include <QDir>
#include <QIcon>

#include "game_window.h"
#include "ui_gamewindow.h"
#include "game_window.h"
#include "objectlabel.h"

#include "model.h"
#include "base_enity.h"
#include "entities.h"

class ObjectLabel;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    //setup the game timer and connect it to the model update
    timer = new QTimer(this);
    timer->setInterval(100);
    timer->start();
    connect(timer, &QTimer::timeout, this, &GameWindow::timerHit);

    image_dir = QDir(":/images/");

    //set up models initial state
    Model::instance()->singleGameStart();
    for (BaseEntity *e : Model::instance()->getRecentlyCreated()){
        createObjectLabel(e);
    }
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::timerHit()
{
    //loop through models new entity collection
    for (BaseEntity *e : Model::instance()->getRecentlyCreated()){
        createObjectLabel(e);
    }
    Model::instance()->update();

    //debugg
    Model::instance()->printState();
}


void GameWindow::createObjectLabel(BaseEntity *entity){
    //the image the object label will have
    QIcon image;

    //see if the image is in our .qrc files if not set it to the missing image pic
    if ( image_dir.exists(QString::fromStdString(entity->getImage()+".png")) ){
        image = QIcon(":/images/"+QString::fromStdString(entity->getImage())+".png");
    } else {
        image = QIcon(":/images/image_missing.png");
    }


    //see if the entity is a component sense they need a special form of the object label.
    ComponentEntity *draggable = dynamic_cast<ComponentEntity*>(entity);
    if(draggable == NULL){
        ObjectLabel *label = new ObjectLabel(this, this, entity, image);
    } else {
        DraggableLabel *label = new DraggableLabel(this, this, entity, image);
    }

}
