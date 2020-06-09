#ifndef BASEPLATFORM_H
#define BASEPLATFORM_H

#include <QGraphicsPixmapItem>

#include "define.h"

class BasePlatform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BasePlatform(platformType platType=NORMAL, objectType objType=PLATFORM, QString resPath=PLATFORM_PATH);
    void setCoordinate(qreal x, qreal y);
    qreal X() const;
    qreal Y() const;
    int getHeight() const;
protected:
    qreal xPos, yPos;
    int platformHeight;
};

#endif // PLATFORM_H
