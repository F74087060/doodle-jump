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
    connect(timer, SIGNAL(timeout()), this, SLOT(movePlatform()));
    connect(timer, SIGNAL(timeout()), this, SLOT(generatePlatform()));
    connect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));

    initPlayer();
    initPlatform();
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

void GameController::initPlayer()
{
    player->setPos(VIEW_WIDTH/2-PLAYER_WIDTH/2,VIEW_HEIGHT/2);
    scene.addItem(player);
}

void GameController::initPlatform()
{
    BasePlatform *platformPointer;
    for(unsigned long i=0;i<PLATFORM_ONSCREEN;i++){
        i==0?platformPointer=new NormalPlatform:platformPointer=randomPlatform();
        plat.push_back(platformPointer);
        plat.at(i)->setCoordinate(i==0?VIEW_WIDTH/2-PLATFORM_WIDTH/2:rand()%(VIEW_WIDTH-PLATFORM_WIDTH)
                                  ,(VIEW_HEIGHT-plat.at(i)->getHeight())-static_cast<int>(i)*((VIEW_HEIGHT-plat.at(i)->getHeight())/PLATFORM_ONSCREEN));
        plat.at(i)->setPos(plat.at(i)->X(),plat.at(i)->Y());
        platformList.append(plat.at(i));
    }
    platformGroup=scene.createItemGroup(platformList);
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
    if(plat.at(0)->y()>=VIEW_HEIGHT){
        double temp=VIEW_HEIGHT-plat.at(0)->y();
        platformList.removeAt(0);
        plat.erase(plat.begin());
        plat.push_back(randomPlatform());
        plat.back()->setCoordinate(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),-1*temp);
        plat.back()->setPos(plat.back()->X(),plat.back()->Y());
        platformList.append(plat.back());
    }
    scene.destroyItemGroup(platformGroup);
    platformGroup=scene.createItemGroup(platformList);
}

void GameController::gameOverSlot()
{
    disconnect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(movePlatform()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(generatePlatform()));

    connect(this, SIGNAL(gameOver()), QApplication::activeWindow(), SLOT(close()));
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
