#include "Emulator.h"
#include "Obstacle.h"
#include <QTime>
#include <QtMath>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

Emulator::Emulator(QTimer* timer, QGraphicsScene* scene, Wheelbase *wb) : wheelbase(wb) {
    /* Add Obstacles */
    Obstacle rod1(300,3,0,253);
    scene->addItem(&rod1);
    Obstacle rod2(300,3,847,253);
    scene->addItem(&rod2);
    Obstacle rod3(1000,3,0,47);
    scene->addItem(&rod3);
    Obstacle pole1(16,16,300,246);
    scene->addItem(&pole1);
    Obstacle pole2(16,16,566,246);
    scene->addItem(&pole2);
    Obstacle pole3(16,16,832,246);
    scene->addItem(&pole3);
    Obstacle pole4(16,16,433,396);
    scene->addItem(&pole4);
    Obstacle pole5(16,16,699,396);
    scene->addItem(&pole5);
    /* End */

    scene->addItem(wheelbase);
    scene->setSceneRect(0,0,1000,665); //same as view

    connect(timer, SIGNAL(timeout()), this, SLOT(blah()));
    timer->start(10);
}

void Emulator::generate_trapazoid(const float &acc_limit, const XYTheta &target, Wheelbase& wheelbase) {
    static float START_VEL = 0;
    static Vec2 cur_pos = {0,0};
    static RTOmega cur_vel = {{0,0},0};
    static float last_tick = 0;
    if (get_ticks() - last_tick > 30) {
        last_tick = get_ticks();
        cur_pos = wheelbase.get_pos();
        cur_vel = {{0,0},0};
    }
    float dT = (float)(get_ticks() - last_tick) / 1000.0;
    float err_x = target.x - cur_pos.x;
    float err_y = target.y - cur_pos.y;
    float s = qSqrt(err_x*err_x + err_y*err_y);
    float tar_vel = qSqrt(2*acc_limit*s + START_VEL*START_VEL);

    if (tar_vel > (cur_vel.v.r + acc_limit * dT))
        cur_vel.v.r += acc_limit * dT;
    else if (tar_vel < (cur_vel.v.r - acc_limit * dT))
        cur_vel.v.r -= acc_limit * dT;
    else
        cur_vel.v.r = tar_vel;

    cur_vel.v.theta = atan2(err_y, err_x);

    Vec2 vdt = polar2vec(polar_mul(dT, cur_vel.v));
    cur_pos = addv2(cur_pos, vdt);

    last_tick = get_ticks();
    //START_VEL = cur_vel.v.r;

    if (fabs(cur_pos.x - target.x) < 5 && fabs(cur_pos.y - target.y) < 5) {
        wheelbase.set_vel({0,0,0});
        return;
    }

    wheelbase.set_vel(RTOmega2XYTheta(cur_vel));
   // XYTheta debug = RTOmega2XYTheta(cur_vel);
//    qDebug() << err_x << " " << err_y;
}

void Emulator::blah() {
    static XYTheta target = {
        .x = 800,
        .y = 150,
        .theta = 0,
    };
    generate_trapazoid(100,target, *wheelbase);
    wheelbase->move();
}
