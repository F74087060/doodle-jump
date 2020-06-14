#ifndef PLATFORM_H
#define PLATFORM_H

#include "baseplatform.h"

class BoostPlatform: public BasePlatform
{
public:
    BoostPlatform();
    virtual ~BoostPlatform();

    void setPlatform();
};

#endif // PLATFORM_H
