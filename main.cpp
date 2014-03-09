#include "mainwindow.h"
#include "game_window.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

<<<<<<< HEAD
    if(argv[1] == "-tests")
    {
        unitTests();
    }

=======
>>>>>>> 73fe4e9ba836b6742e62416ad85ea1eaf32ac01d
    MainWindow w;

    w.show();
    
    return a.exec();
}
