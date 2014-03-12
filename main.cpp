#include "mainwindow.h"
#include "game_window.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Game_Window g;

    MainWindow w;

    w.show();
    
    return a.exec();
}
