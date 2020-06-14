#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "define.h"

class GameController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeScene(QGraphicsScene *scene);
public slots:
    void showMainMenu();
    void newGame();
private:
    Ui::MainWindow *ui;

    void initScene();
    void startGame();

    QGraphicsScene *scene, *sceneMain;
    QGraphicsView *view;

    GameController *controller;
};

#endif // MAINWINDOW_H
