#include "EmulatorView.h"

EmulatorView::EmulatorView(QWidget *parent) : QGraphicsView(parent) {}

void EmulatorView::initialise(QGraphicsScene *scene) {
    setScene(scene);
    setFixedSize(1000,665); //size of robocon field in cm
    setBackgroundBrush(QBrush(QImage(":/images/background.png")));
}
