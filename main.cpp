#include <iostream>
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
#include <mainwindow.h>
#include <EmulatorView.h>

using namespace std;
QElapsedTimer *TIME = new QElapsedTimer();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Omni Wheelbase Emulator");
    mainWindow.show();

    TIME->start();

    return a.exec();
}
