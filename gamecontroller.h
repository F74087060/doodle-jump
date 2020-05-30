#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsScene>
#include <QTimer>

#include "define.h"
#include "player.h"

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent=nullptr);
private:
    QGraphicsScene &scene;
    QTimer *timer;

    Player *player;
};

#endif // GAMECONTROLLER_H
