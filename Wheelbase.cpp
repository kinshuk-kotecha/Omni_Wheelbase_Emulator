#include "Wheelbase.h"
#include "Obstacle.h"
#include <QTimer>
#include <QDebug>
#include <QTime>

Wheelbase::Wheelbase() {
    /* set size and initial position */
    setRect(0,0,90,90);
    setPos(0,160);
    /* make wheelbase focusable */
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    /* connect timer with move() */
    //connect(timer, SIGNAL(timeout()), this, SLOT(move()));
}

void Wheelbase::set_vel(const XYTheta& velocity){
    vel = velocity;
}

Vec2 Wheelbase::get_pos() const {
    Vec2 pos;
    pos.x = x()+45;
    pos.y = y()+45;
    return pos;
}

void Wheelbase::move() {
    /* Detect Collisions */
    QList<QGraphicsItem *> colliding_items = collidingItems();

    double x_increment = vel.x*(0.01)*0.8; //apply friction
    double y_increment = vel.y*(0.01)*0.8;
    if (colliding_items.size() > 0) {
        setPos(x(), y());
    }
    else
        setPos(x()+x_increment, y()+y_increment);
    //qDebug() << x_increment;
}

WheelSpeed Wheelbase::get_wheel_speed(const XYTheta& velocity) {
    return wheel_speed = {
        .wheels[0].r = static_cast<float>(velocity.x * (-cos45) + velocity.y * (-sin45) - velocity.theta),
        .wheels[1].r = static_cast<float>(velocity.x * (-cos45) + velocity.y * (sin45) - velocity.theta),
        .wheels[2].r = static_cast<float>(velocity.x * (cos45) + velocity.y * (-sin45) - velocity.theta),
        .wheels[3].r = static_cast<float>(velocity.x * (cos45) + velocity.y * (sin45) - velocity.theta)
    };
}
