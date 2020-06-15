#include "projectile.h"
#include <QDebug>

Projectile::Projectile()
{
    setShapeMode(HeuristicMaskShape);

    setPixmap(QPixmap(PROJECTILE_PATH));
    QTimer *timer=new QTimer();
    timer->start(16);

    setData(TYPE, PROJECTILE);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
}

void Projectile::move()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==HAZARD){
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
                scene()->removeItem(this);
                delete this;
            }
        }
    }

    setPos(x(), y()-10);
    if(y()<=0-pixmap().height()){
        scene()->removeItem(this);
        delete this;
    }
}
