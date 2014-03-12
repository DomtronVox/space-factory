#include "mainwindow.h"
#include "game_window.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //GameWindow g;
    //g.show();

    MainWindow w;

    w.show();
    
    return a.exec();
}
