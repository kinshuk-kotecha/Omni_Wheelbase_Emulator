#ifndef WHEELBASE_H
#define WHEELBASE_H

#include <QGraphicsRectItem>
#include <QObject>
#include "helper.h"

class Wheelbase : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Wheelbase();
    void set_vel(const XYTheta& velocity);
    Vec2 get_pos() const;
public slots:
    void move();
private:
    XYTheta vel;
    WheelSpeed wheel_speed;
    WheelSpeed get_wheel_speed(const XYTheta& velocity);
    friend class Emulator;
};

extern Wheelbase *wheelbase;

#endif
