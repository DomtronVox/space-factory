#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game_window.h"
#include "highscores.h"
#include "model.h"

#include <cassert>
#include <iostream>

using namespace std;

void unitTests() {
    string selectedSavedGame;
    //assert(Model::instance()->motherModel->load(selectedSavedGame)->getMap()->getId() == 0);

    HighScore scores;
    scores.addScore("Robert", 10);
    scores.addScore("Phillip", 30);
    scores.addScore("Michael", 20);
    Score* first = scores.getScores().at(0);

    assert(first->getName() == "Phillip");
    scores.addScore("Rebecca", 5);
    Score* last = scores.getScores().back();
    assert(last->getName() == "Rebecca");
    for(int i = 0; i < scores.getScores().size(); i++)
    {
        Score* s = scores.getScores().at(i);
        cout << s->getName() << endl;
    }

    HighScore loadScores;
    loadScores.load();
    for(int i = 0; i < loadScores.getScores().size(); i++)
    {
        Score* s = loadScores.getScores().at(i);
        cout << s->getName() << endl;
    }


    //model test for starting a new game. TODO: rework this to use asserts
    Model::instance()->singleGameStart();
    assert(Model::instance()->getById(0) != NULL);

    //update 5 times so the factory has finished building it's first component
    Model::instance()->update(); Model::instance()->update();
    Model::instance()->update();
    assert(Model::instance()->getById(1)==NULL);
    Model::instance()->update();
    assert(Model::instance()->getById(1)!=NULL);

    Model::instance()->reset();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //unitTests();

    ui->setupUi(this);

    //set the help and score screens to be invisible
    ui->brwHelp->hide();
    ui->boxHighScores->hide();
    ui->lstScores->addItem("Names  --  Scores");

    //TODO: uncomment the section below and modify once model has been implemented as a singlton class
    //vector<chr *> lines = Model::instance().getHighScores()->getFormatedScores();
    //for (string line : lines)
    //    ui->lstScores->addItem(line);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    Game_Window *gameWindow = new Game_Window;
    gameWindow->show();
    this->hide();
}
