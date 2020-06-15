#include <cstdlib>

#include "randomplatform.h"

bool dropTracker;

BasePlatform *randomPlatform()
{
    int index=random()%50;
    if(dropTracker==false){
        index<2?index=DROP:(index<10?index=BOOST:index=NORMAL);
    }
    else{
        index<4?index=BOOST:index=NORMAL;
    }
    BasePlatform *basePointer;

    switch(index){
        case BOOST:
            basePointer = new BoostPlatform;
            dropTracker=false;
            break;
        case DROP:
            basePointer = new StopPlatform;
            dropTracker=true;
            break;
        default:
            basePointer = new NormalPlatform;
            dropTracker=false;
            break;
    }
    return basePointer;
}
