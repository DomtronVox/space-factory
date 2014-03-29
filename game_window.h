#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QDir>

#include "base_entity.h"
#include "objectlabel.h"


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GameWindow(QString difficulty, QWidget *parent = 0);
    ~GameWindow();

    
private:
    Ui::GameWindow *ui;

    QTimer *timer;
    QDir image_dir;


    void timerHit();

    void createObjectLabel(BaseEntity *entity);

    // deletes an object label from the screen with the <id> number
    void deleteOjbectLabel(int id);
};

#endif // GAME_WINDOW_H
