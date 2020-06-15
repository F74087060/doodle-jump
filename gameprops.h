#ifndef GAMEPROPS_H
#define GAMEPROPS_H

#include <QGraphicsPixmapItem>

#include "define.h"

class GameProps: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameProps();
    virtual ~GameProps();
};

#endif // GAMEPROPS_H
