#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "model.h"
#include "objectlabel.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    
private:
    Ui::GameWindow *ui;
};



#endif // GAMEWINDOW_H
