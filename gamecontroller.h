#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <ctime>
#include <cstdlib>

#include <vector>

#include <QApplication>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QList>

#include "define.h"
#include "player.h"
#include "randomplatform.h"
#include "button.h"
#include "mainwindow.h"

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QGraphicsView &view, QObject *parent=nullptr);
    QGraphicsItemGroup *platformGroup;

    std::vector<BasePlatform *> plat;
private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

    void initPlayer();
    void initPlatform();
    void initGameOverScene();

    QGraphicsScene &scene, *pauseScene, *gameOverScene;
    QGraphicsView &view;
    QList<QGraphicsItem *> platformList;
    QTimer *timer, *timer2;

    Player *player;

    bool paused=false;
signals:
    void gameOver();
public slots:
    void movePlatform();
    void generatePlatform();
    void gameOverSlot();
protected:
    bool eventFilter(QObject *object, QEvent *event);
    void advance(int phase);
};

#endif // GAMECONTROLLER_H
