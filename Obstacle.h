#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsRectItem>
#include <QObject>
#include "helper.h"

class Obstacle : public QObject, public QGraphicsRectItem {
public:
    Obstacle(float size_x, float size_y, float pos_x, float pos_y);
};

#endif // OBSTACLE_H
