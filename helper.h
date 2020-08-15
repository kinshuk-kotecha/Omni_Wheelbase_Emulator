#ifndef HELPER_H
#define HELPER_H

#define sin45 (0.707107)
#define cos45 (0.707107)

struct XYTheta {
    float x;
    float y;
    float theta;
};

struct PolarVec {
    float r;
    float theta;
};

struct WheelSpeed {
    PolarVec wheels[4];
};

#endif // HELPER_H
