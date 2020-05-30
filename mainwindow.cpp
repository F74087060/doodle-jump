#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(this)),
    controller(new GameController(*scene, this))
{
    initScene();
    startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    view->setScene(scene);
}
