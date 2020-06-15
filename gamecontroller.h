#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <ctime>
#include <cstdlib>

#include <vector>

#include <QApplication>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include <QFont>

#include "define.h"
#include "player.h"
#include "randomplatform.h"
#include "button.h"
#include "mainwindow.h"
#include "ghost.h"
#include "fallingplatform.h"

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController();
    GameController(QGraphicsScene &scene, QGraphicsView &view, QObject *parent=nullptr);
    QGraphicsItemGroup *platformGroup;

    std::vector<BasePlatform *> plat;
private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

    void initPlayer();
    void initPlatform();
    void initGhost();
    void initFallingPlatform();
    void initGameOverScene();
    void showScore();

    QGraphicsScene *tempScene, &scene, *pauseScene, *gameOverScene;
    QGraphicsView *tempView, &view;
    QList<QGraphicsItem *> platformList;
    QTimer *timer;
    QGraphicsTextItem *label;

    Player *player;
    Ghost *ghost;
    FallingPlatform *fallingPlatform;

    bool paused=false;
    double fallingPlatformSpeed;
    int score;
signals:
    void gameOver();
    void scoreUpdated();
public slots:
    void moveCamera();
    void entityMovementGeneration();
    void generatePlatform();
    void moveGhost();
    void generateGhost();
    void moveFallingPlatform();
    void generateFallingPlatform();
    void addScore();
    void setScore();
    void gameOverSlot();
protected:
    bool eventFilter(QObject *object, QEvent *event);
    void advance(int phase);
};

#endif // GAMECONTROLLER_H
