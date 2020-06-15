#include "fallingplatform.h"

FallingPlatform::FallingPlatform()
{
    srand(static_cast<unsigned>(time(nullptr)));

    setHazard();
}

FallingPlatform::~FallingPlatform()
{
}

void FallingPlatform::setHazard()
{
    QPixmap pix;
    pix.load(FALLING_PLATFORM_PATH);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    setData(HAZARD_TYPE, FALLING_PLATFORM);
}
