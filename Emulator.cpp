#include "Emulator.h"
#include "Obstacle.h"
#include <QTime>
#include <QtMath>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

Emulator::Emulator(QTimer* timer, QGraphicsScene* scene, Wheelbase *wb) : wheelbase(wb), target(Vec2toXYTheta(wb->get_pos())), acc_limit(0), opt_pos(target) {
    /* Add Obstacles */
    obstacles[0] = new Obstacle(300,3,0,253);
    obstacles[1] = new Obstacle(300,3,847,253);
    obstacles[2] = new Obstacle(1000,3,0,47);
    obstacles[3] = new Obstacle(16,16,300,246);
    obstacles[4] = new Obstacle(16,16,566,246);
    obstacles[5] = new Obstacle(16,16,832,246);
    obstacles[6] = new Obstacle(16,16,433,396);
    obstacles[7] = new Obstacle(16,16,699,396);
    for (int i = 0; i < 8; i++) {
        scene->addItem(obstacles[i]);
    }
    /* End */

    scene->addItem(wheelbase);
    scene->setSceneRect(0,0,1000,665); //same as view

    connect(timer, SIGNAL(timeout()), this, SLOT(emulate()));
    timer->start(10);
}

Emulator::~Emulator() {
    delete wheelbase;
    for (int i = 0; i < 8; i++) {
        delete obstacles[i];
    }
}

XYTheta Emulator::generate_trapezoid(const float &acc_limit, const XYTheta &target, Wheelbase& wheelbase, XYTheta& opt_pos) {
    static float END_VEL = 0;
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
    float tar_vel = qSqrt(2*acc_limit*s + END_VEL*END_VEL);

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

    if (fabs(cur_pos.x - target.x) < 5 && fabs(cur_pos.y - target.y) < 5) {
        wheelbase.set_opt_vel({0,0,0});
        opt_pos = target;
        return RTOmega2XYTheta({{0,0},0});
    }

    opt_pos = (XYTheta) { .x = cur_pos.x, .y = cur_pos.y, .theta = 0};
    return RTOmega2XYTheta(cur_vel);
}

void Emulator::set_acc_limit(const float &limit) {
    (limit > 300) ? acc_limit = 300 : acc_limit = limit;
}

void Emulator::set_target(const XYTheta &tar) {
    target = tar;
}

void Emulator::PID(const XYTheta &opt_pos, XYTheta &opt_vel, PIDMode mode) {
    PIDError err;
}

void Emulator::emulate() {
    static XYTheta opt_vel;
    opt_vel = generate_trapezoid(100, target, *wheelbase, opt_pos);
    wheelbase->set_opt_vel(opt_vel);
    wheelbase->move();
}

PIDError Emulator::calc_pid_err(const XYTheta &opt_pos, const XYTheta &opt_vel, PIDError &err) {

}
