#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //unitTest();

    QApplication a(argc, argv);

    GameWindow g;
    g.show();

    MainWindow w;

    w.show();
    
    return a.exec();
}
