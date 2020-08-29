#ifndef HELPER_H
#define HELPER_H

#include <QElapsedTimer>
#include <QtMath>

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

struct Vec2 {
    float x;
    float y;
};

struct RTOmega {
    PolarVec v;
    float a; //angle -- equivalent to XYTheta's theta -- angle of rotation
};

enum PIDMode {
    Trapezoid,
    Bezier,
    N_PIDModes,
};

struct PIDError {
    XYTheta p;
    XYTheta i;
    XYTheta d;
};

typedef PIDError PIDGain;

extern QElapsedTimer *TIME;

#define get_ticks() TIME->elapsed()
#define MAX_ACC_LIMIT 350
#define MAX_VEL 400
#define MAX_ACC 300

Vec2 polar2vec(const PolarVec& p);
XYTheta RTOmega2XYTheta(const RTOmega& p);
PolarVec polar_mul(const float& k, const PolarVec& p);
Vec2 addv2(const Vec2& u, const Vec2& v);
XYTheta Vec2toXYTheta(const Vec2& v);
XYTheta sub_xyt(const XYTheta& a, const XYTheta& b);
XYTheta add_xyt(const XYTheta& a, const XYTheta& b);
XYTheta mul_xyt(const XYTheta& a, const XYTheta& b);
RTOmega XYTheta2RTOmega(const XYTheta& p);


#endif // HELPER_H
