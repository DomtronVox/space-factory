#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //unit_tests();

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
    return a.exec();
}
