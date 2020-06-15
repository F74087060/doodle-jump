#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    sceneMain(new QGraphicsScene(this)),
    view(new QGraphicsView(this)),
    controller(new GameController())
{
    initScene();
    showMainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeScene(QGraphicsScene *scene)
{
    view->setScene(scene);
}

void MainWindow::showMainMenu()
{
    sceneMain->setBackgroundBrush(QBrush(QImage(MAIN_MENU_PATH)));

    Button *playButton = new Button(PLAY_PATH, PLAY_HOVER_PATH);
    sceneMain->addItem(playButton);
    playButton->setPos(3*VIEW_WIDTH/4-BUTTON_WIDTH/2, 575);

    connect(playButton, SIGNAL(clicked()), this, SLOT(newGame()));
    changeScene(sceneMain);
}

void MainWindow::newGame()
{
    scene->clear();
    delete controller;
    controller=new GameController(*scene, *view, this);
    startGame();
}

void MainWindow::initScene()
{
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(VIEW_WIDTH,VIEW_HEIGHT);
    view->setSceneRect(0,0,VIEW_WIDTH,VIEW_HEIGHT);
    view->fitInView(0,0,VIEW_WIDTH,VIEW_HEIGHT,Qt::KeepAspectRatio);

    ui->setupUi(this);
    setCentralWidget(view);
}

void MainWindow::startGame()
{
    scene->setBackgroundBrush(QBrush(QImage(BACKGROUND_PATH)));
    changeScene(scene);
}
