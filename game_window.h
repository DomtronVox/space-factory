#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QDir>

#include "base_enity.h"
#include "objectlabel.h"


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    
private:
    Ui::GameWindow *ui;

    QTimer *timer;
    QDir image_dir;


    void timerHit();
    void createObjectLabel(BaseEntity *entity);
};

#endif // GAME_WINDOW_H
