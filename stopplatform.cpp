#include "stopplatform.h"

StopPlatform::StopPlatform():BasePlatform ()
{
    setPlatform();
}

StopPlatform::~StopPlatform()
{
}

void StopPlatform::setPlatform()
{
    QPixmap pix;
    pix.load(STOP_PLATFORM_PATH);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, DROP);
}
