#include <cstdlib>

#include "randomplatform.h"

BasePlatform *randomPlatform()
{
    int index=random()%NUMBER_OF_PLATFORM;
    BasePlatform *basePointer;

    switch(index){
        case BOOST:
            basePointer = new BoostPlatform;
            break;
        default:
            basePointer = new NormalPlatform;
            break;
    }
    return basePointer;
}
