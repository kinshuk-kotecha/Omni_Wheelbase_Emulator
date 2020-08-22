#ifndef EMULATOR_H
#define EMULATOR_H

#include "helper.h"
#include "Wheelbase.h"
#include "Obstacle.h"

class Emulator : public QObject {
    Q_OBJECT
public:
    Emulator(QTimer* timer, QGraphicsScene* scene, Wheelbase *wheelbase);
    ~Emulator();
    XYTheta generate_trapezoid(const float& acc_limit, const XYTheta& target, Wheelbase& wheelbase, XYTheta& opt_pos);
    void set_acc_limit(const float& limit);
    void set_target(const XYTheta& tar);
    void set_mode(const PIDMode& pid_mode);
    void set_pid_gains(const PIDGain& gains);
    void PID(const XYTheta& opt_pos, XYTheta& opt_vel, PIDMode mode);
public slots:
    void emulate();
private:
    Wheelbase *wheelbase;
    XYTheta target;
    float acc_limit;
    XYTheta opt_pos;
    Obstacle* obstacles[8];
    PIDGain pid_gains[N_PIDModes];
    PIDMode mode;
    PIDError calc_pid_err(const XYTheta& opt_pos, const XYTheta& opt_vel, PIDError& err);
    void clamp_integral(PIDError& err, const XYTheta& clamp_values);
    XYTheta apply_pid_gains(const PIDError& err, const PIDMode& mode);
};

#endif // EMULATOR_H
