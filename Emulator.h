#ifndef EMULATOR_H
#define EMULATOR_H

#include "helper.h"
#include "Wheelbase.h"

class Emulator : public QObject {
    Q_OBJECT
public:
    Emulator(QTimer* timer);
    void generate_trapazoid(const float& acc_limit, const XYTheta& target, Wheelbase& wheelbase);
public slots:
    void blah();
};

#endif // EMULATOR_H
