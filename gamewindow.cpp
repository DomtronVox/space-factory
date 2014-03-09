#include <QTimer>
#include <QDir>
#include <QIcon>

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "objectlabel.h"

#include "model.h"
#include "base_enity.h"
#include "entities.h"


GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    //setup the game timer and connect it to the model update
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &GameWindow::timerHit);

    image_dir = QDir(":/images/");

    //g.show();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::timerHit()
{
    //loop through models new entity collection
    for (BaseEntity *e : Model::instance()->getRecentlyCreated()){

        QIcon image;

        if ( image_dir.exists(e->getImage()) ){
            image = QIcon(":/images/"+QString(e->getImage()));
        } else {
            image = QIcon(":/images/image_missing.png");
        }


        //see if the entity is a component sense they need a special form of the object label.
        ComponentEntity *draggable = dynamic_cast<ComponentEntity*>(e);

        if(draggable == NULL){
            DraggableLabel *label = new DraggableLabel(this, this, e, image);
        } else {
            ObjectLabel *label = new ObjectLabel(this, this, e, image);
        }
    }
    Model::instance()->update();
}

