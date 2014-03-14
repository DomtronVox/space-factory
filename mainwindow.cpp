#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game_window.h"
#include "highscores.h"
#include "model.h"
#include <cassert>
#include <iostream>

using namespace std;

void unitTests() {

    HighScore scores;
    scores.addScore("Robert", 10);
    scores.addScore("Phillip", 30);
    scores.addScore("Michael", 20);
    Score* s = scores.getScores().at(0);

    assert(s->getName() == "Phillip");
    scores.addScore("Rebecca", 5);
    s = scores.getScores().back();
    assert(s->getName() == "Rebecca");
    scores.save();

    HighScore loadScores;
    loadScores.load();
    loadScores.addScore("Rhonda", 65);
    s = loadScores.getScores().at(0);

    assert(s->getName() == "Rhonda");
    assert(s->getScore() == 65);
    loadScores.save();
    remove ("highscores.txt");

    //model test for starting a new game. TODO: rework this to use asserts
    Model::instance()->singleGameStart();
    assert(Model::instance()->getById(0) != NULL);

    assert(Model::instance()->load());

    /*
    //update 5 times so the factory has finished building it's first component
    for(int i = 0; i < 4; i++) {
        Model::instance()->update();
    }
    assert(Model::instance()->getById(1)==NULL);
    Model::instance()->update();
    assert(Model::instance()->getById(1)!=NULL);

    Model::instance()->reset();
    */
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //unitTests();

    //populate highscores list
    HighScore scores;
    scores.load();
    for(int i = 0; i < scores.getScores().size(); ++i )
    {
        Score *score = scores.getScores().at(i);
        QString QName = QString::fromStdString(score->getName());
        QString QScore = QString::number(score->getScore());
        ui->lstScores->addItem(QName + " -- " + QScore);

    }

    //connect(ui->btnNewGame, SIGNAL(click()), this, SLOT(openGameWindow()));
    //set the help and score screens to be invisible
    ui->brwHelp->hide();
    ui->boxHighScores->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openGameWindow()
{
    GmWdw = new GameWindow();

    GmWdw->show();
}


//toggle between showing the help window and not showing it
void MainWindow::on_btnHelp_toggled(bool checked)
{
    if (checked) {
        //show browser
        ui->brwHelp->show();

        //hide other menu elements
        ui->btnLoadGame->hide();
        ui->btnScores->hide();
        ui->boxNewGameGroup->hide();
        ui->btnExit->hide();

        //Change the buttons text to close
        ui->btnHelp->setText("Close");

    } else {
        //show browser
        ui->brwHelp->hide();

        //hide other menu elements
        ui->btnLoadGame->show();
        ui->btnScores->show();
        ui->boxNewGameGroup->show();
        ui->btnExit->show();

        //Change the buttons text to close
        ui->btnHelp->setText("How To Play");
    }
}

void MainWindow::on_btnScores_toggled(bool checked)
{
    if (checked) {
        //show score list
        ui->boxHighScores->show();

        //hide other menu elements
        ui->btnLoadGame->hide();
        ui->btnHelp->hide();
        ui->boxNewGameGroup->hide();
        ui->btnExit->hide();

        //Change the buttons text to close
        ui->btnScores->setText("Close");

    } else {
        //hide score list
        ui->boxHighScores->hide();

        //hide other menu elements
        ui->btnLoadGame->show();
        ui->btnHelp->show();
        ui->boxNewGameGroup->show();
        ui->btnExit->show();

        //Change the buttons text to close
        ui->btnScores->setText("High Scores");

    }
}

void MainWindow::on_btnExit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_btnNewGame_clicked()
{
    openGameWindow();
    this->hide();
}
