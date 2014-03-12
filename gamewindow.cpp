#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

/*
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    g.show();
}

GameWindow::~GameWindow()
{
    delete ui;
}
*/
