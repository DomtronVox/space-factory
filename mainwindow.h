#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gamewindow.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openGameWindow();

private:
    GameWindow *GmWdw;

private slots:
    void on_btnHelp_toggled(bool checked);

    void on_btnScores_toggled(bool checked);

    void on_btnExit_clicked();

    void on_btnNewGame_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW
