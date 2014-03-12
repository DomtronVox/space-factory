#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>

namespace Ui {
class Game_Window;
}

class Game_Window : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Game_Window(QWidget *parent = 0);
    ~Game_Window();
    
private:
    Ui::Game_Window *ui;
};

#endif // GAME_WINDOW_H
