#include "platform.h"

Platform::Platform()
{
    QPixmap pix;
    pix.load(":/resource/pngguru.com.png");

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
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
