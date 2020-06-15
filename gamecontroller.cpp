#include "gamecontroller.h"
#include <QDebug>

GameController::GameController():
    tempScene(new QGraphicsScene(this)),
    scene(*tempScene),
    tempView(new QGraphicsView()),
    view(*tempView)
{

}

GameController::GameController(QGraphicsScene &scene, QGraphicsView &view, QObject *parent):
    QObject(parent),
    scene(scene),
    pauseScene(new QGraphicsScene(this)),
    gameOverScene(new QGraphicsScene(this)),
    view(view),
    timer(new QTimer(this)),
    label(new QGraphicsTextItem),
    player(new Player(*this)),
    ghost(new Ghost()),
    fallingPlatform(new FallingPlatform()),
    score(0)
{
    srand(static_cast<unsigned>(time(nullptr)));

    scene.installEventFilter(this);

    timer->start(16);
    connect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    connect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
    connect(timer, SIGNAL(timeout()), this, SLOT(entityMovementGeneration()));
    connect(timer, SIGNAL(timeout()), ghost, SLOT(moveLeft()));
    connect(timer, SIGNAL(timeout()), ghost, SLOT(moveRight()));
    connect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
    connect(this, SIGNAL(scoreUpdated()), this, SLOT(setScore()));

    initPlayer();
    initPlatform();
    initGhost();
    initFallingPlatform();
    initGameOverScene();
    showScore();
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
        case Qt::Key_Escape: case Qt::Key_P:
            if(paused==false){
                disconnect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));
                disconnect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
                disconnect(timer, SIGNAL(timeout()), this, SLOT(entityMovementGeneration()));
                disconnect(timer, SIGNAL(timeout()), ghost, SLOT(moveLeft()));
                disconnect(timer, SIGNAL(timeout()), ghost, SLOT(moveRight()));
                disconnect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));

                paused=true;
            }
            else{
                connect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));
                connect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
                connect(timer, SIGNAL(timeout()), this, SLOT(entityMovementGeneration()));
                connect(timer, SIGNAL(timeout()), ghost, SLOT(moveLeft()));
                connect(timer, SIGNAL(timeout()), ghost, SLOT(moveRight()));
                connect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));

                paused=false;
            }
            break;
        case Qt::Key_Space:
            QPixmap pix;
            pix.load(PLAYER_SHOOT_PATH);
            player->setPixmap(pix.scaledToWidth(PLAYER_WIDTH));

            projectile=new Projectile();
            projectile->setPos(player->x()-5, player->y()-player->getPlayerHeight()/2);
            scene.addItem(projectile);
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

void GameController::initGhost()
{
    scene.addItem(ghost);
    ghost->setPos(rand()%(VIEW_WIDTH/2-GHOST_WIDTH/2)+(VIEW_WIDTH/4-GHOST_WIDTH/2),
                  -1*rand()%(VIEW_HEIGHT*GHOST_RARITY)-VIEW_HEIGHT);
}

void GameController::initFallingPlatform()
{
    scene.addItem(fallingPlatform);
    fallingPlatform->setPos(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),
                           -1*rand()%(VIEW_HEIGHT*FALLING_PLATFORM_RARITY));
}

void GameController::initGameOverScene()
{
    gameOverScene->setBackgroundBrush(QBrush(QImage(BACKGROUND_PATH)));
}

void GameController::showScore()
{
    label->setFont(QFont("courier", 35));
    label->setDefaultTextColor(Qt::black);
    label->setPos(OFFSET,OFFSET);
    label->setZValue(2);
    scene.addItem(label);
}

void GameController::setScore()
{
    label->setPlainText(QString::number(score));
}

void GameController::moveCamera()
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
        ghost->setY(ghost->y()+player->getDeltaY());
        fallingPlatform->setY(fallingPlatform->y()+player->getDeltaY());
        addScore();
    }
}

void GameController::entityMovementGeneration()
{
    generatePlatform();
    moveGhost();
    generateGhost();
    moveFallingPlatform();
    generateFallingPlatform();
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

void GameController::moveGhost()
{
    switch(ghost->currentDirection){
        case LEFT:
            emit ghost->leftSignal();
            break;
        case RIGHT:
            emit ghost->rightSignal();
            break;
        default:
            break;
    }

    if(ghost->now<ghost->minX){
        ghost->currentDirection=RIGHT;
    }
    else if(ghost->now>ghost->maxX){
        ghost->currentDirection=LEFT;
    }

    if(ghost->now>0){
        ghost->setX(ghost->x()-ghost->speed);
    }
    else {
        ghost->setX(ghost->x()+ghost->speed);
    }

    if(ghost->x()>=VIEW_WIDTH-GHOST_WIDTH/2){
        ghost->setX(-1*GHOST_WIDTH/2);
    }
    else if(ghost->x()+GHOST_WIDTH/2<=0){
        ghost->setX(VIEW_WIDTH-GHOST_WIDTH/2);
    }

}

void GameController::generateGhost()
{
    if(ghost->y()>=VIEW_HEIGHT+OFFSET){
        ghost->minX=-1*rand()%MOVE_RANGE;
        ghost->maxX=-1*ghost->minX;
        ghost->speed=rand()%3+1;
        ghost->setY(-1*((rand()%(VIEW_HEIGHT*GHOST_RARITY)-OFFSET)));
        ghost->setPos(rand()%(VIEW_WIDTH/2-GHOST_WIDTH/2)+(VIEW_WIDTH/4-GHOST_WIDTH/2),
                      -1*rand()%(VIEW_HEIGHT*GHOST_RARITY)-VIEW_HEIGHT);
    }
}

void GameController::moveFallingPlatform()
{
    fallingPlatform->setY(fallingPlatform->y()+10);
}

void GameController::generateFallingPlatform()
{
    if(fallingPlatform->y()>=VIEW_HEIGHT+OFFSET){
        fallingPlatform->setPos(rand()%(VIEW_WIDTH-PLATFORM_WIDTH)+PLATFORM_WIDTH,
                               -1*rand()%(VIEW_HEIGHT*FALLING_PLATFORM_RARITY));
    }
}

void GameController::checkProjectile()
{

}

void GameController::addScore()
{
    score+=player->getDeltaY();
    emit scoreUpdated();
}

void GameController::gameOverSlot()
{
    disconnect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(generatePlatform()));

    label->setFont(QFont("courier", 100));
    label->setDefaultTextColor(Qt::black);
    label->setPos(OFFSET,OFFSET+80);
    label->setZValue(2);
    label->setTextWidth(VIEW_WIDTH-OFFSET/2);
    gameOverScene->addItem(label);

    QGraphicsTextItem *label2=new QGraphicsTextItem();
    label2->setFont(QFont("courier", 70));
    label2->setDefaultTextColor(Qt::red);
    label2->setPos(OFFSET,OFFSET);
    label2->setZValue(2);
    label2->setPlainText("gameover");
    gameOverScene->addItem(label2);

    Button *menuButton = new Button(MENU_PATH, MENU_HOVER_PATH);
    gameOverScene->addItem(menuButton);
    menuButton->setPos(3*VIEW_WIDTH/4-BUTTON_WIDTH/2, 575);

    connect(menuButton, SIGNAL(clicked()), QApplication::activeWindow(), SLOT(showMainMenu()));

    view.setScene(gameOverScene);
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
