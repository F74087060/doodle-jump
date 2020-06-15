#include "player.h"
#include "gamecontroller.h"
#include <QDebug>

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
    setZValue(2);

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
                    previousY=static_cast<BasePlatform *>(collidingItem)->Y();
                    if(collidingItem->data(PLATFORM_TYPE)==DROP)
                        boostFactor=0;
                    else if(collidingItem->data(PLATFORM_TYPE)==BOOST)
                        boostFactor=2;
                    else
                        boostFactor=1;
                return true;
            }
        }
        return false;
    }
}

bool Player::collidesWithHazard()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
        return false;
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==HAZARD){
                if(currentDirection==DOWN){
                    jump();
                    if(collidingItem->data(HAZARD_TYPE)==GHOST){
                        scene()->removeItem(collidingItem);
                        Ghost *ghost=static_cast<Ghost *>(collidingItem);
                        ghost->minX=-1*rand()%MOVE_RANGE;
                        ghost->maxX=-1*ghost->minX;
                        ghost->speed=rand()%3+1;
                        ghost->setY(-1*((rand()%(VIEW_HEIGHT*GHOST_RARITY)-OFFSET)));
                        ghost->setPos(rand()%(VIEW_WIDTH/2-GHOST_WIDTH/2)+(VIEW_WIDTH/4-GHOST_WIDTH/2),
                                      -1*rand()%(VIEW_HEIGHT*GHOST_RARITY)-VIEW_HEIGHT);
                        scene()->addItem(collidingItem);
                    }
                    else if(collidingItem->data(HAZARD_TYPE)==FALLING_PLATFORM){
                        scene()->removeItem(collidingItem);
                        collidingItem->setPos(rand()%(VIEW_WIDTH-PLATFORM_WIDTH)+PLATFORM_WIDTH,
                                               -1*rand()%(VIEW_HEIGHT*FALLING_PLATFORM_RARITY));
                        scene()->addItem(collidingItem);
                    }
                    return false;
                }
                return true;
            }
        }
        return false;
    }
}

void Player::collidesWithMultiplier()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
        return;
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==GAMEPROPS){
                if(collidingItem->data(GAMEPROPS_TYPE)==MULTIPLIER){
                    controller.mul->incrementCount();
                    if(controller.mul->count>=5){
                        scene()->removeItem(controller.mul);
                    }
                    else{
                        collidingItem->setPos(rand()%(VIEW_WIDTH-GHOST_WIDTH)+GHOST_WIDTH,
                                               -1*rand()%(VIEW_HEIGHT*MULTIPLIER_RARITY));
                    }
                }
                else if(collidingItem->data(GAMEPROPS_TYPE)==SPRING_BOOTS){
                    springBootsFactor==2?springBootsFactor=1:springBootsFactor=2;
                    scene()->removeItem(collidingItem);
                    controller.bootsNotInScene=true;
                }
            }
        }
    }
}

double Player::getDeltaY() const
{
    return deltaY;
}

void Player::jump()
{
    setFall(UP);
    deltaY=initialVelocity*boostFactor*springBootsFactor;
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

double Player::getGravity() const
{
    return gravity;
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
        emit controller.gameOver();
    }
    boostFactor=1;
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

    if(collidesWithHazard()){
        emit controller.gameOver();
    }
    collidesWithMultiplier();
}
