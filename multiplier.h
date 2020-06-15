#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "define.h"
#include "gameprops.h"

class Multiplier: public GameProps
{
public:
    Multiplier();
    virtual ~Multiplier();

    void incrementCount();

    int count=0;
private:
    void setMultiplier();
    void changePix();
};

#endif // MULTIPLIER_H
