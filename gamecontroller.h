#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <ctime>
#include <cstdlib>

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>

#include "define.h"
#include "player.h"
#include "platform.h"

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent=nullptr);
private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

    QGraphicsScene &scene;
    QTimer *timer;

    Player *player;
    Platform *plat[10];
protected:
    bool eventFilter(QObject *object, QEvent *event);
    void advance(int phase);
};

#endif // GAMECONTROLLER_H
