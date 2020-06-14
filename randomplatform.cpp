#include <cstdlib>

#include "randomplatform.h"

BasePlatform *randomPlatform()
{
    int index=random()%50;
    index<2?index=DROP:(index<10?index=BOOST:index=NORMAL);
    BasePlatform *basePointer;

    switch(index){
        case BOOST:
            basePointer = new BoostPlatform;
            break;
        case DROP:
            basePointer = new StopPlatform;
            break;
        default:
            basePointer = new NormalPlatform;
            break;
    }
    return basePointer;
}
