#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <algorithm>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "define.h"

class GameController;

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(GameController &controller);

    void moveDirection(horizontalDirection direction);
    bool checkMovingDirection(horizontalDirection direction);
    bool collidesWithPlayer();
    double getDeltaY() const;
    void jump();
    void setDeltaY(double value);
    void setFall(verticalDirection direction);
    qreal getDistanceToGround() const;
    verticalDirection getCurrentDirection() const;
    qreal getPlayerHeight() const;
    double previousY;

private:
    GameController &controller;

    qreal playerHeight, distanceToGround;
    verticalDirection currentDirection;
    horizontalDirection movingDirection;

    const double initialVelocity, gravity;
    double deltaY=25;
    int boostFactor=1;
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
