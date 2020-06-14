#ifndef BASEPLATFORM_H
#define BASEPLATFORM_H

#include <QGraphicsPixmapItem>

#include "define.h"

class BasePlatform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BasePlatform();
    virtual ~BasePlatform();

    void setCoordinate(qreal x, qreal y);
    qreal X() const;
    qreal Y() const;
    int getHeight() const;

    virtual void setPlatform()=0;
protected:
    qreal xPos, yPos;
    int platformHeight;
};

#endif // PLATFORM_H
