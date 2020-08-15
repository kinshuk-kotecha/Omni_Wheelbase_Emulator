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
    wheelbase->setRect(0,0,100,100);

    scene->addItem(wheelbase);

    wheelbase->setFlag(QGraphicsItem::ItemIsFocusable);
    wheelbase->setFocus();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setScene(scene);
    view->setFixedSize(1000,665); //size of robocon field in cm
    scene->setSceneRect(0,0,1000,665);
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    view->show();

    return a.exec();
}
