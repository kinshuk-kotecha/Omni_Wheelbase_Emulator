#ifndef WHEELBASE_H
#define WHEELBASE_H

#include <QGraphicsRectItem>
#include <QObject>
#include "helper.h"

class Wheelbase : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Wheelbase();
    void set_vel(XYTheta velocity);
public slots:
    void move();
private:
    XYTheta vel;
    WheelSpeed wheel_speed;
    WheelSpeed get_wheel_speed(XYTheta velocity);
};


#endif
