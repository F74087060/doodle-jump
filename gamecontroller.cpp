#include "gamecontroller.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent):
    QObject(parent),
    scene(scene),
    timer(new QTimer(this)),
    player(new Player(*this))
{
    srand(static_cast<unsigned>(time(nullptr)));

    scene.installEventFilter(this);

    timer->start(16);
    connect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));

    player->setPos(VIEW_WIDTH/2-PLAYER_WIDTH/2,VIEW_HEIGHT/2);
    scene.addItem(player);

    for(unsigned long i=0;i<8;i++){
        plat.push_back(new Platform());
        plat.at(i)->setCoordinate(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),rand()%(VIEW_HEIGHT-plat.at(i)->getHeight()));
        plat.at(i)->setPos(plat.at(i)->getX(),plat.at(i)->getY());
        scene.addItem(plat.at(i));
    }
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            player->moveDirection(LEFT);
            break;
        case Qt::Key_Right:
            player->moveDirection(RIGHT);
            break;
    }
}

void GameController::handleKeyRelease(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            if(player->checkMovingDirection(LEFT))
                player->moveDirection(STOP);
            break;
        case Qt::Key_Right:
            if(player->checkMovingDirection(RIGHT))
                player->moveDirection(STOP);
            break;
    }
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if(event->type()==QEvent::KeyPress){
        handleKeyPressed(static_cast<QKeyEvent *>(event));
        return true;
    }
    else if(event->type()==QEvent::KeyRelease){
        handleKeyRelease(static_cast<QKeyEvent *>(event));
        return true;
    }
    else{
        return QObject::eventFilter(object, event);
    }
}
