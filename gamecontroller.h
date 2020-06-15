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
#include "projectile.h"
#include "multiplier.h"
#include "springboots.h"

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController();
    GameController(QGraphicsScene &scene, QGraphicsView &view, QObject *parent=nullptr);
    QGraphicsItemGroup *platformGroup;

    std::vector<BasePlatform *> plat;
    Multiplier *mul;

    bool bootsNotInScene=true;
private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

    void initialize();
    void initPlayer();
    void initPlatform();
    void initGhost();
    void initFallingPlatform();
    void initMultiplier();
    void initGameOverScene();
    void showScore();
    void setMultiplier();

    QGraphicsScene *tempScene, &scene, *pauseScene, *gameOverScene;
    QGraphicsView *tempView, &view;
    QList<QGraphicsItem *> platformList;
    QTimer *timer;
    QGraphicsTextItem *label;

    Player *player;
    Projectile *projectile;
    Ghost *ghost;
    FallingPlatform *fallingPlatform;
    SpringBoots *springBoots;

    bool paused=false;
    double fallingPlatformSpeed;
    int score, multiplier[5];
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
    void generateMultiplier();
    void removeSpringBoots();
    void addScore();
    void setScore();
    void gameOverSlot();
protected:
    bool eventFilter(QObject *object, QEvent *event);
    void advance(int phase);
};

#endif // GAMECONTROLLER_H
