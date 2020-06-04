#include "platform.h"

platform::platform(qreal x, qreal y)
{
    xPos=x;
    yPos=y;

    QPixmap pix;
    pix.load(":/resource/pngguru.com.png");

    setPixmap(pix.scaledToWidth(PLAYER_WIDTH));
}
