#include "platform.h"

Platform::Platform()
{
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    QPixmap pix;
    pix.load(PLATFORM_PATH);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
    setData(TYPE, PLATFORM);
}

void Platform::setCoordinate(qreal x, qreal y)
{
    xPos=x;
    yPos=y;
}

qreal Platform::getX()
{
    return xPos;
}

qreal Platform::getY()
{
    return yPos;
}

int Platform::getHeight()
{
    return platformHeight;
}
