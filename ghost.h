#ifndef GHOST_H
#define GHOST_H

#include <cstdlib>

#include "hazards.h"

class Ghost: public QObject, public Hazards
{
    Q_OBJECT
public:
    Ghost();
    virtual ~Ghost();

    void setHazard();
    void setDirection(horizontalDirection direction);

    horizontalDirection currentDirection;
    qreal minX, maxX, now;

    int speed;
signals:
    void leftSignal();
    void rightSignal();
public slots:
    void moveLeft();
    void moveRight();
};

#endif // GHOST_H
