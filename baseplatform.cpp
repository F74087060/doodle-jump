#include "baseplatform.h"

BasePlatform::BasePlatform(platformType platType, objectType objType, QString resPath)
{
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    QPixmap pix;
    pix.load(resPath);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
    setData(TYPE, objType);
    setData(PLATFORM_TYPE, platType);
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
