#include "multiplier.h"

Multiplier::Multiplier()
{
    setMultiplier();
}

Multiplier::~Multiplier()
{
}

void Multiplier::setMultiplier()
{
    QPixmap pix;
    pix.load(MULTIPLIER_PATH_1);

    setPixmap(pix.scaledToWidth(GHOST_WIDTH));
    setData(GAMEPROPS_TYPE, MULTIPLIER);
}

void Multiplier::incrementCount()
{
    count++;
    changePix();
}

void Multiplier::changePix()
{
    QPixmap pix;
    switch (count) {
        case 0:
            pix.load(MULTIPLIER_PATH_1);
            break;
        case 1:
            pix.load(MULTIPLIER_PATH_3);
            break;
        case 2:
            pix.load(MULTIPLIER_PATH_5);
            break;
        case 3:
            pix.load(MULTIPLIER_PATH_10);
            break;
        case 4:
            pix.load(MULTIPLIER_PATH_200);
            break;
    }
    setPixmap(pix.scaledToWidth(GHOST_WIDTH));
}
