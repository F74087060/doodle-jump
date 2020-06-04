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

    void moveDirection(horizontalDirection direction);
    bool checkMovingDirection(horizontalDirection direction);
private:
    void setFall(verticalDirection direction);

    GameController &controller;

    int playerHeight;
    verticalDirection currentDirection;
    horizontalDirection movingDirection;
    double dy=25;

    const double initialVelocity, gravity;
signals:
    void upSignal();
    void downSignal();
    void leftSignal();
    void rightSignal();
public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
protected:
    void advance(int phase);
};

#endif // PLAYER_H
