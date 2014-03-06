#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //unit_tests();

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    //GameWindow g;
    //g.show();
    
    return a.exec();
}
