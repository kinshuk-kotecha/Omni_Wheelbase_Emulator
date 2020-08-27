#include "Emulator.h"
#include "Obstacle.h"
#include <QTime>
#include <QtMath>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

Emulator::Emulator(QTimer* timer, QGraphicsScene* scene, Wheelbase *wb) : wheelbase(wb), target(Vec2toXYTheta(wb->get_pos())), acc_limit(0), opt_pos(target), mode(Trapezoid) {
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

    /* Initialize pid_gains */
    for (int i = 0; i < N_PIDModes; i++) {
        pid_gains[i] = {{50,20,0},{50,20,0},{0,0,0}};
    }

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

float Emulator::get_acc_limit() {
    return acc_limit;
}

void Emulator::set_target(const XYTheta &tar) {
    target = tar;
}

void Emulator::set_mode(const PIDMode &pid_mode) {
    mode = pid_mode;
}

void Emulator::set_pid_gains(const PIDGain &gains)
{
    pid_gains[mode] = gains;
}

void Emulator::PID(const XYTheta &opt_pos, XYTheta &opt_vel, PIDMode mode) {
    PIDError err = {{0,0,0},{0,0,0},{0,0,0}};
    err = calc_pid_err(opt_pos, opt_vel, err);
    XYTheta clamp_values = {10,10,1};
    clamp_integral(err, clamp_values);
    XYTheta gains = apply_pid_gains(err, mode);
    opt_vel = add_xyt(opt_vel, gains);
}

void Emulator::emulate() {
    static XYTheta opt_vel;
    opt_vel = generate_trapezoid(100, target, *wheelbase, opt_pos);
    PID(opt_pos,opt_vel,mode);
    limit_vel_gain(opt_vel,wheelbase->get_opt_velocity(),0.01);
    wheelbase->set_opt_vel(opt_vel);
    wheelbase->move();
}

PIDError Emulator::calc_pid_err(const XYTheta &opt_pos, const XYTheta &opt_vel, PIDError &previous_err) {
    XYTheta pos_err = sub_xyt(opt_pos, Vec2toXYTheta(wheelbase->get_pos()));
    XYTheta vel_err = sub_xyt(opt_vel, wheelbase->get_real_velocity());
    PIDError pid_err = (PIDError){
            .p = pos_err,
            .i = add_xyt(previous_err.i,pos_err),
            .d = vel_err,
    };

    if (fabs(pid_err.p.x) < 1 && fabs(pid_err.d.x) < 1) {
        pid_err.p.x = 0; pid_err.d.x = 0;
    }
    if (fabs(pid_err.p.y) < 1 && fabs(pid_err.d.y) < 1) {
        pid_err.p.y = 0; pid_err.d.y = 0;
    }
    if (fabs(pid_err.p.theta) < 1 && fabs(pid_err.d.theta) < 1) {
        pid_err.p.theta = 0; pid_err.d.theta = 0;
    }
    return pid_err;
}

void Emulator::clamp_integral(PIDError &err, const XYTheta &clamp_values) {
    err.i.x = fmax(fmin(err.i.x, clamp_values.x),-clamp_values.x);
    err.i.y = fmax(fmin(err.i.y, clamp_values.y),-clamp_values.y);
    err.i.theta = fmax(fmin(err.i.theta, clamp_values.theta),-clamp_values.theta);
}

XYTheta Emulator::apply_pid_gains(const PIDError &err, const PIDMode& mode) {
    PIDGain gain = pid_gains[mode];
    XYTheta out = mul_xyt(gain.p, err.p);
    out = add_xyt(out, mul_xyt(gain.d, err.d));
    out = add_xyt(out, mul_xyt(gain.i, err.i));
    return out;
}

void Emulator::apply_acc_limit(float &tar_vel, const RTOmega &cur_vel, const float& dT) {
    if (tar_vel > (cur_vel.v.r + MAX_ACC * dT))
        tar_vel = cur_vel.v.r + MAX_ACC * dT;
    else if (tar_vel < (cur_vel.v.r - MAX_ACC * dT))
        tar_vel = cur_vel.v.r - MAX_ACC * dT;
    else
        tar_vel = cur_vel.v.r;
}

void Emulator::limit_vel_gain(XYTheta &tar_vel, const XYTheta& cur_vel, const float& dT) {
    /* limit x vel */
    if (tar_vel.x > (cur_vel.x + MAX_ACC * dT))
        tar_vel.x = cur_vel.x + MAX_ACC * dT;
    else if (tar_vel.x < (cur_vel.x - MAX_ACC * dT))
        tar_vel.x = cur_vel.x - MAX_ACC * dT;
    else
        tar_vel.x = cur_vel.x;

    /* limit y vel */
    if (tar_vel.y > (cur_vel.y + MAX_ACC * dT))
        tar_vel.y = cur_vel.y + MAX_ACC * dT;
    else if (tar_vel.y < (cur_vel.y - MAX_ACC * dT))
        tar_vel.y = cur_vel.y - MAX_ACC * dT;
    else
        tar_vel.y = cur_vel.y;
}

/* TODO
 * Overshooting
 */

