#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "define.h"
#include "ghost.h"

class Projectile: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projectile();
public slots:
    void move();
};

#endif // PROJECTILE_H
