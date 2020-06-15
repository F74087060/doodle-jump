#include "springboots.h"

SpringBoots::SpringBoots()
{
    setSpringBoots();
}

SpringBoots::~SpringBoots()
{
}

void SpringBoots::setSpringBoots()
{
    QPixmap pix;
    pix.load(SPRING_BOOTS_PATH);

    setPixmap(pix.scaledToWidth(SPRING_BOOTS_WIDTH));
    setData(GAMEPROPS_TYPE, SPRING_BOOTS);
}
