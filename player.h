#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

#include "define.h"

class GameController;

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(GameController &controller);
private:
    GameController &controller;

    int playerHeight;
    freefall currentDirection;
    double dy=25;
    const double initialVelocity, gravity;

    void setFall(freefall direction);
    void moveUp();
    void moveDown();

protected:
    void advance(int phase);
};

#endif // PLAYER_H
