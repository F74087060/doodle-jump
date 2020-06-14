#include "boostplatform.h"

BoostPlatform::BoostPlatform():BasePlatform()
{
    setPlatform();
}

BoostPlatform::~BoostPlatform()
{
}

void BoostPlatform::setPlatform()
{
    QPixmap pix;
    pix.load(BOOST_PLATFORM_PATH);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
    setData(PLATFORM_TYPE, BOOST);
}
