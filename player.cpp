#include "player.h"

Player::Player(GameController &controller):
    controller(controller),
    currentDirection(DOWN),
    movingDirection(STOP),
    initialVelocity(20),
    gravity(0.5)
{
    connect(this, SIGNAL(upSignal()), this, SLOT(moveUp()));
    connect(this, SIGNAL(downSignal()), this, SLOT(moveDown()));
    connect(this, SIGNAL(leftSignal()), this, SLOT(moveLeft()));
    connect(this, SIGNAL(rightSignal()), this, SLOT(moveRight()));

    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

    dy=initialVelocity;
    QPixmap pix;
    pix.load(":/resource/pngfind.com-minions-png-3009522.png");

    setPixmap(pix.scaledToWidth(PLAYER_WIDTH));
    playerHeight=pix.scaledToWidth(PLAYER_WIDTH).height();
}

void Player::moveDirection(horizontalDirection direction)
{
    if(movingDirection==LEFT&&direction==LEFT)
        return;
    if(movingDirection==RIGHT&&direction==RIGHT)
        return;
    movingDirection=direction;
}

bool Player::checkMovingDirection(horizontalDirection direction)
{
    return (direction==movingDirection)?true:false;
}

bool Player::collidesWithPlatform()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
        return false;
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==PLATFORM)
                return true;
        }
        return false;
    }
}

double Player::getdy()
{
    return dy;
}

void Player::jump()
{
    setFall(UP);
    dy=initialVelocity;
}

void Player::setFall(verticalDirection direction)
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

void Player::moveLeft()
{
    setPos(x()-3,y());
    if(x()+PLAYER_WIDTH/2<=0){
        setPos(VIEW_WIDTH-PLAYER_WIDTH/2,y());
    }
}

void Player::moveRight()
{
    setPos(x()+3,y());
    if(x()>=VIEW_WIDTH-PLAYER_WIDTH/2){
        setPos(-1*PLAYER_WIDTH/2,y());
    }
}

void Player::advance(int phase)
{
    if(!phase){
        return;
    }
    switch(currentDirection){
        case UP:
            emit upSignal();
            break;
        case DOWN:
            emit downSignal();
            if(collidesWithPlatform()){
                jump();
            }
            break;
    }
    switch(movingDirection){
        case LEFT:
            emit leftSignal();
            break;
        case RIGHT:
            emit rightSignal();
            break;
        case STOP:
            break;
    }

}
