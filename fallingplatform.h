#ifndef FALLINGPLATFORM_H
#define FALLINGPLATFORM_H

#include <cstdlib>

#include "hazards.h"

class FallingPlatform: public QObject, public Hazards
{
    Q_OBJECT
public:
    FallingPlatform();
    virtual ~FallingPlatform();

    void setHazard();
};

#endif // FALLINGPLATFORM_H
