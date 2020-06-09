#include "player.h"
#include "gamecontroller.h"

Player::Player(GameController &controller):
    controller(controller),
    currentDirection(DOWN),
    movingDirection(STOP),
    initialVelocity(20),
    gravity(0.65)
{
    connect(this, SIGNAL(upSignal()), this, SLOT(moveUp()));
    connect(this, SIGNAL(downSignal()), this, SLOT(moveDown()));
    connect(this, SIGNAL(leftSignal()), this, SLOT(moveLeft()));
    connect(this, SIGNAL(rightSignal()), this, SLOT(moveRight()));

    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    setZValue(1);

    deltaY=initialVelocity;
    QPixmap pix;
    pix.load(PLAYER_RIGHT_PATH);

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
            if(collidingItem->data(TYPE)==PLATFORM&&collidingItem->y()-playerHeight+OFFSET>=y()){
                distanceToGround=VIEW_HEIGHT-collidingItem->y();
                previousY=static_cast<BasePlatform *>(collidingItem)->getY();
                return true;
            }
        }
        return false;
    }
}

double Player::getDeltaY() const
{
    return deltaY;
}

void Player::jump()
{
    setFall(UP);
    deltaY=initialVelocity;
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

qreal Player::getDistanceToGround() const
{
    return distanceToGround;
}

verticalDirection Player::getCurrentDirection() const
{
    return currentDirection;
}

qreal Player::getPlayerHeight() const
{
    return playerHeight;
}

void Player::setDeltaY(double value)
{
    deltaY = value;
}

void Player::moveUp()
{
    deltaY-=gravity;
    setPos(x(), y()-deltaY);
    if(deltaY<=0){
        setFall(DOWN);
        deltaY=0;
    }
}

void Player::moveDown()
{
    deltaY+=(gravity);
    setPos(x(), y()+deltaY);
    if(y()+playerHeight>VIEW_HEIGHT){
        setFall(UP);
        deltaY=initialVelocity;
    }
}

void Player::moveLeft()
{
    QPixmap pix;
    pix.load(PLAYER_LEFT_PATH);
    setPixmap(pix.scaledToWidth(PLAYER_WIDTH));

    setPos(x()-8,y());
    if(x()+PLAYER_WIDTH/2<=0){
        setPos(VIEW_WIDTH-PLAYER_WIDTH/2,y());
    }
}

void Player::moveRight()
{
    QPixmap pix;
    pix.load(PLAYER_RIGHT_PATH);
    setPixmap(pix.scaledToWidth(PLAYER_WIDTH));

    setPos(x()+8,y());
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
