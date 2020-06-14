#include "baseplatform.h"

BasePlatform::BasePlatform()
{
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
}

BasePlatform::~BasePlatform()
{
}

void BasePlatform::setCoordinate(qreal x, qreal y)
{
    xPos=x;
    yPos=y;
}

qreal BasePlatform::X() const
{
    return xPos;
}

qreal BasePlatform::Y() const
{
    return yPos;
}

int BasePlatform::getHeight() const
{
    return platformHeight;
}
