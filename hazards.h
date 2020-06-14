#ifndef HAZARDS_H
#define HAZARDS_H

#include <QGraphicsPixmapItem>

#include "define.h"

class Hazards: public QGraphicsPixmapItem
{
public:
    Hazards();
    virtual ~Hazards();

    void setCoordinate(qreal x, qreal y=-OFFSET);

    virtual void setHazard()=0;
protected:
    qreal xPos, yPos;
};

#endif // HAZARDS_H
