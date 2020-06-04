#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>

#include "define.h"

class Platform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Platform();
    void setCoordinate(qreal x, qreal y);
    qreal getX();
    qreal getY();
    int getHeight();
private:
    qreal xPos, yPos;
    int platformHeight;
};

#endif // PLATFORM_H
