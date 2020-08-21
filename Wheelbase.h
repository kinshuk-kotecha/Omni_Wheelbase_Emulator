#ifndef WHEELBASE_H
#define WHEELBASE_H

#include <QGraphicsRectItem>
#include <QObject>
#include "helper.h"

class Wheelbase : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Wheelbase();
    void set_opt_vel(const XYTheta& velocity);
    XYTheta get_opt_velocity() const;
    XYTheta get_real_velocity() const;
    Vec2 get_pos() const;
public slots:
    void move();
private:
    XYTheta opt_vel;
    XYTheta real_vel;
    WheelSpeed wheel_speed;
    WheelSpeed get_wheel_speed(const XYTheta& velocity);
};

extern Wheelbase *wheelbase;

#endif
