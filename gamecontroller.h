#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <ctime>
#include <cstdlib>

#include <vector>

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "define.h"
#include "player.h"
#include "randomplatform.h"

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent=nullptr);
    QGraphicsItemGroup *platformGroup;

    std::vector<BasePlatform *> plat;
private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

    void initPlayer();
    void initPlatform();

    QGraphicsScene &scene;
    QList<QGraphicsItem *> platformList;
    QTimer *timer, *timer2;

    Player *player;
public slots:
    void movePlatform();
    void generatePlatform();
protected:
    bool eventFilter(QObject *object, QEvent *event);
    void advance(int phase);
};

#endif // GAMECONTROLLER_H
