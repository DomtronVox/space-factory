#include "game_window.h"
#include "ui_game_window.h"

Game_Window::Game_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_Window)
{
    ui->setupUi(this);
}

Game_Window::~Game_Window()
{
    delete ui;
}
