#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //unitTest();

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    GameWindow g;
    g.show();
    
    return a.exec();
}
