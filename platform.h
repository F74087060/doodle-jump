#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>

#include "define.h"

class platform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    platform(qreal x, qreal y);
private:
    qreal xPos, yPos;
};

#endif // PLATFORM_H
