#include "baseplatform.h"

BasePlatform::BasePlatform()
{
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    QPixmap pix;
    pix.load(PLATFORM_PATH);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
    setData(TYPE, PLATFORM);
}

void BasePlatform::setCoordinate(qreal x, qreal y)
{
    xPos=x;
    yPos=y;
}

qreal BasePlatform::getX() const
{
    return xPos;
}

qreal BasePlatform::getY() const
{
    return yPos;
}

int BasePlatform::getHeight() const
{
    return platformHeight;
}
