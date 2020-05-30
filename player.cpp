#include "player.h"

Player::Player(GameController &controller):
    controller(controller),
    currentDirection(DOWN),
    initialVelocity(20),
    gravity(0.5)
{
    dy=initialVelocity;
    QPixmap pix;
    pix.load(":/resource/pngfind.com-minions-png-3009522.png");

    setPixmap(pix.scaledToWidth(PLAYER_WIDTH));
    playerHeight=pix.scaledToWidth(PLAYER_WIDTH).height();
}

void Player::setFall(freefall direction)
{
    if(currentDirection==UP&&direction==UP){
        return;
    }
    if(currentDirection==DOWN&&direction==DOWN){
        return;
    }
    currentDirection=direction;
}

void Player::moveUp()
{
    dy-=gravity;
    setPos(x(), y()-dy);
    if(dy<=0){
        setFall(DOWN);
        dy=0;
    }
}

void Player::moveDown()
{
    dy+=(gravity/2.5);
    setPos(x(), y()+dy);
    if(y()+playerHeight>VIEW_HEIGHT){
        setFall(UP);
        dy=initialVelocity;
    }
}

void Player::advance(int phase)
{
    if(!phase){
        return;
    }
    switch(currentDirection){
        case UP:
            moveUp();
            break;
        case DOWN:
            moveDown();
            break;
    }

}
