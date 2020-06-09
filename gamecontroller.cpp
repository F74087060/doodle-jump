#include "gamecontroller.h"
#include <QDebug>

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
    connect(timer, SIGNAL(timeout()), this, SLOT(movePlatform()));
    connect(timer, SIGNAL(timeout()), this, SLOT(generatePlatform()));

    player->setPos(VIEW_WIDTH/2-PLAYER_WIDTH/2,VIEW_HEIGHT/2);
    scene.addItem(player);

    for(unsigned long i=0;i<8;i++){
        plat.push_back(new BasePlatform());
        plat.at(i)->setCoordinate(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),rand()%(VIEW_HEIGHT-plat.at(i)->getHeight()));
        plat.at(i)->setPos(plat.at(i)->getX(),plat.at(i)->getY());
        platformList.append(plat.at(i));
    }
    platformGroup=scene.createItemGroup(platformList);
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

void GameController::movePlatform()
{
    if(player->y()<VIEW_HEIGHT/2-player->getPlayerHeight()){
        if(player->y()<VIEW_HEIGHT/2-player->getPlayerHeight()){
            player->setY(VIEW_HEIGHT/2-player->getPlayerHeight());
        }
        std::vector<BasePlatform *>::iterator it=plat.begin();
        for(unsigned long i=0;it!=plat.end();it++, i++){
            if(player->getCurrentDirection()==UP){
                    plat.at(i)->setY(plat.at(i)->y()+player->getDeltaY());
            }
        }
    }
}

void GameController::generatePlatform()
{
    std::vector<BasePlatform *>::iterator it=plat.begin();
    for(unsigned long i=0;it!=plat.end();it++, i++){
        if(plat.at(i)->y()>VIEW_HEIGHT+40){
            plat.at(i)->setCoordinate(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),(rand()%40-40));
            plat.at(i)->setPos(plat.at(i)->getX(),plat.at(i)->getY());
        }
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
