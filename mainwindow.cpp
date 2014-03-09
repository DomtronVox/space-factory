#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "highscores.h"
#include "model.h"
#include <cassert>

void unitTests() {
    Model * motherModel = new Model;
    string selectedSavedGame;
    //assert(motherModel->load(selectedSavedGame)->getMap()->getId() == 0);

    /*HighScore scores;
    scores.addScore("Robert", 10);
    scores.addScore("Phillip", 30);
    scores.addScore("Michael", 20);
    scores.sortScores();
    Score* first = scores.getScores().at(0);
    assert(first->getName() == "Phillip");
    */
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    unitTests();

    //set the help and score screens to be invisible
    ui->brwHelp->hide();
    ui->lstScores->hide();
    ui->lstScores->addItem("High Score");

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
        ui->lstScores->show();

        //hide other menu elements
        ui->btnLoadGame->hide();
        ui->btnHelp->hide();
        ui->boxNewGameGroup->hide();
        ui->btnExit->hide();

        //Change the buttons text to close
        ui->btnScores->setText("Close");

    } else {
        //hide score list
        ui->lstScores->hide();

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
