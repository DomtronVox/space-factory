#include "mainwindow.h"
#include "game_window.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(argv[1] == "-tests")
    {
        unitTests();
    }

    MainWindow w;

    w.show();
    
    return a.exec();
}
