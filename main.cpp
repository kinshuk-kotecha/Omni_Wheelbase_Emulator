#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "Wheelbase.h"
#include <QImage>
#include <QBrush>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    Wheelbase *wheelbase = new Wheelbase();
    scene->addItem(wheelbase);

    QGraphicsView *view = new QGraphicsView(scene);
    view->setScene(scene);
    view->setFixedSize(1000,665); //size of robocon field in cm
    scene->setSceneRect(0,0,1000,665); //same as view
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    view->show();
    wheelbase->set_vel({50,50});

    return a.exec();
}
