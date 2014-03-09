#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    GameWindow g;

    MainWindow w;

    w.show();
    
    return a.exec();
}
