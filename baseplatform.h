#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>

#include "define.h"

class BasePlatform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BasePlatform();
    void setCoordinate(qreal x, qreal y);
    qreal getX() const;
    qreal getY() const;
    int getHeight() const;
private:
    qreal xPos, yPos;
    int platformHeight;
};

#endif // PLATFORM_H
