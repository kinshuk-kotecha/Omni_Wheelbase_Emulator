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
    XYTheta generate_trapezoid(const float& acc_limit, const XYTheta& target, Wheelbase& wheelbase);
    void set_acc_limit(const float& limit);
    void set_target(const XYTheta& tar);
public slots:
    void emulate();
private:
    Wheelbase *wheelbase;
    XYTheta target;
    float acc_limit;
    Obstacle* obstacles[8];
};

#endif // EMULATOR_H
