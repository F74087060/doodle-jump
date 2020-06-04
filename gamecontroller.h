#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QKeyEvent>
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
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);

    QGraphicsScene &scene;
    QTimer *timer;

    Player *player;
protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // GAMECONTROLLER_H
