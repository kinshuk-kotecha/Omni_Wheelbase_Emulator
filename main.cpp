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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    QTimer *timer = new QTimer();
    Wheelbase *wheelbase = new Wheelbase();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setScene(scene);
    view->setFixedSize(1000,665); //size of robocon field in cm
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    view->show();

    TIME->start();

    Emulator *emulator = new Emulator(timer, scene, wheelbase);

    return a.exec();
}
