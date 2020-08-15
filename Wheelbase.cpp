#include "Wheelbase.h"
#include <QTimer>

Wheelbase::Wheelbase() {
    /* set size and initial position */
    setRect(0,0,90,90);
    setPos(0,160);
    /* make wheelbase focusable */
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    /* connect timer with move() */
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Wheelbase::set_vel(XYTheta velocity){
    vel = velocity;
}

void Wheelbase::move(XYTheta velocity) {
    WheelSpeed ws = get_wheel_speed(velocity);
}

WheelSpeed Wheelbase::get_wheel_speed(XYTheta velocity) {
    return wheel_speed = {
        .wheels[0] = static_cast<float>(velocity.x * (-cos45) + velocity.y * (-sin45) - velocity.theta),
        .wheels[1] = static_cast<float>(velocity.x * (-cos45) + velocity.y * (sin45) - velocity.theta),
        .wheels[2] = static_cast<float>(velocity.x * (cos45) + velocity.y * (-sin45) - velocity.theta),
        .wheels[3] = static_cast<float>(velocity.x * (cos45) + velocity.y * (sin45) - velocity.theta)
    };
}
