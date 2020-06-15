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
