#include "ghost.h"

Ghost::Ghost():Hazards(),
    currentDirection(RIGHT),
    now(0),
    speed(1)
{
    srand(static_cast<unsigned>(time(nullptr)));

    minX=-1*rand()%MOVE_RANGE;
    maxX=-1*minX;

    connect(this, SIGNAL(leftSignal()), this, SLOT(moveLeft()));
    connect(this, SIGNAL(rightSignal()), this, SLOT(moveRight()));

    setHazard();
}

Ghost::~Ghost()
{
}

void Ghost::setHazard()
{
    QPixmap pix;
    pix.load(GHOST_PATH);

    setPixmap(pix.scaledToWidth(GHOST_WIDTH));
    setData(HAZARD_TYPE, GHOST);
}

void Ghost::setDirection(horizontalDirection direction)
{
    if(currentDirection==LEFT&&direction==LEFT){
        return;
    }
    if(currentDirection==RIGHT&&direction==RIGHT){
        return;
    }
    currentDirection=direction;
}

void Ghost::moveLeft()
{
    now-=1;
}

void Ghost::moveRight()
{
    now+=1;
}
