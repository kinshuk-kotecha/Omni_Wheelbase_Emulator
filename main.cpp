#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "Wheelbase.h"
#include "Obstacle.h"
#include "Emulator.h"
#include <QImage>
#include <QBrush>
#include <QElapsedTimer>
#include <QDebug>
#include <QTimer>

QElapsedTimer *TIME = new QElapsedTimer();
QTimer *timer = new QTimer();
Wheelbase *wheelbase = new Wheelbase(timer);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(wheelbase);

    /* add obstacles */
    Obstacle *rod1 = new Obstacle(300,3,0,253);
    scene->addItem(rod1);
    Obstacle *rod2 = new Obstacle(300,3,847,253);
    scene->addItem(rod2);
    Obstacle *rod3 = new Obstacle(1000,3,0,47);
    scene->addItem(rod3);
    Obstacle *pole1 = new Obstacle(16,16,300,246);
    scene->addItem(pole1);
    Obstacle *pole2 = new Obstacle(16,16,566,246);
    scene->addItem(pole2);
    Obstacle *pole3 = new Obstacle(16,16,832,246);
    scene->addItem(pole3);
    Obstacle *pole4 = new Obstacle(16,16,433,396);
    scene->addItem(pole4);
    Obstacle *pole5 = new Obstacle(16,16,699,396);
    scene->addItem(pole5);
    QGraphicsView *view = new QGraphicsView(scene);

    view->setScene(scene);
    view->setFixedSize(1000,665); //size of robocon field in cm
    scene->setSceneRect(0,0,1000,665); //same as view
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    view->show();
    //wheelbase->set_vel({50,-50});

    TIME->start();

    Emulator *emulator = new Emulator(timer);

    return a.exec();
}
