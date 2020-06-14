#include "normalplatform.h"

NormalPlatform::NormalPlatform():BasePlatform()
{
    setPlatform();
}

NormalPlatform::~NormalPlatform()
{
}

void NormalPlatform::setPlatform()
{
    QPixmap pix;
    pix.load(PLATFORM_PATH);

    setPixmap(pix.scaledToWidth(PLATFORM_WIDTH));
    platformHeight=pix.scaledToWidth(PLATFORM_WIDTH).height();
    setData(TYPE, PLATFORM);
    setData(PLATFORM_TYPE, NORMAL);
}
