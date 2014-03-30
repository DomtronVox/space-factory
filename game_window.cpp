#include <QTimer>
#include <QDir>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>

#include "game_window.h"
#include "ui_gamewindow.h"
#include "game_window.h"
#include "objectlabel.h"

#include "model.h"
#include "base_entity.h"
#include "entities.h"

class ObjectLabel;

GameWindow::GameWindow(QString difficulty, bool cheat, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    ui->gameMenu->addItem("Game Menu");
    ui->gameMenu->addItem("Save Game");
    ui->gameMenu->addItem("Pause Game");
    ui->gameMenu->addItem("Quit Game");

    ui->lblGameOver->hide();

    //setup the game timer and connect it to the model update
    timer = new QTimer(this);
    timer->setInterval(100);
    timer->start();
    connect(timer, &QTimer::timeout, this, &GameWindow::timerHit);

    image_dir = QDir(":/images/");

    //set up models initial state
    Model::instance()->singleGameStart(difficulty.toStdString(), cheat);
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
    bool ok = Model::instance()->update();

    //debug
    Model::instance()->printState();

    for (QObject *obj: ui->centralwidget->children()){
        ObjectLabel *lbl = dynamic_cast<ObjectLabel*>(obj);
        if (lbl != NULL) lbl->updateData();
    }

    // If Save Game is selected
    if(ui->gameMenu->currentIndex() == 1)
    {
        if(Model::instance()->save()){
            QMessageBox::information(this, "Save Game", "Your game has been saved.");
        }
        else
            QMessageBox::critical(this, "Save Game", "Unable to save your game.");

        ui->gameMenu->setCurrentIndex(0);
}
    // If Pause Game is selected
    if(ui->gameMenu->currentIndex() == 2)
    {
        QMessageBox::information(this, "Pause Game", "Game is paused. Press ok to continue game.");
        ui->gameMenu->setCurrentIndex(0);
    }
    // Quit Game
    if(ui->gameMenu->currentIndex() == 3)
    {
        Model::instance()->save();
        QApplication::quit();
    }

    //if model returned false end the game
    if (!ok) {
        ui->lblGameOver->show();
        timer->stop();
    }
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


    //see if the entity is a component since they need a special form of the object label.
    ComponentEntity *draggable = dynamic_cast<ComponentEntity*>(entity);
    if(draggable == NULL){
        ObjectLabel *label = new ObjectLabel(centralWidget(), this, entity, image);
        label->show();
    } else {
        DraggableLabel *label = new DraggableLabel(centralWidget(), this, entity, image);
        label->show();
    }
}
