#include "Wheelbase.h"
#include "Obstacle.h"
#include "helper.h"
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>

Wheelbase::Wheelbase() : opt_vel({0,0,0}), real_vel(opt_vel) {
    /* set size and initial position */
    setRect(0,0,90,90);
    setPos(0,160);
    /* make wheelbase focusable */
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Wheelbase::set_opt_vel(const XYTheta& velocity){
    opt_vel = velocity;
}

XYTheta Wheelbase::get_opt_velocity() const {
    return opt_vel;
}

XYTheta Wheelbase::get_real_velocity() const {
    return real_vel;
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
    QRandomGenerator random(get_ticks());
    /* Apply Random Friction */
    float friction = random.bounded(0.5);
    real_vel.x = opt_vel.x*(1-friction);
    real_vel.y = opt_vel.y*(1-friction);
    double x_increment = real_vel.x*(0.01);
    double y_increment = real_vel.y*(0.01);
    /* Add slipping */
    if (friction < 0.04 + (get_ticks() % 12)/1000) {
        x_increment = 0;
        y_increment = 0;
    }
    if (colliding_items.size() > 0) {
        setPos(x(), y());
    }
    else
        setPos(x()+x_increment, y()+y_increment);
}

WheelSpeed Wheelbase::get_wheel_speed(const XYTheta& velocity) {
    return wheel_speed = {
        .wheels[0].r = static_cast<float>(velocity.x * (-cos45) + velocity.y * (-sin45) - velocity.theta),
        .wheels[1].r = static_cast<float>(velocity.x * (-cos45) + velocity.y * (sin45) - velocity.theta),
        .wheels[2].r = static_cast<float>(velocity.x * (cos45) + velocity.y * (-sin45) - velocity.theta),
        .wheels[3].r = static_cast<float>(velocity.x * (cos45) + velocity.y * (sin45) - velocity.theta)
    };
}
