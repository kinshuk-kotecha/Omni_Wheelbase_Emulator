#include "helper.h"

Vec2 polar2vec(const PolarVec& p) {
    float s = sin(p.theta);
    float c = cos(p.theta);
    return (Vec2) {
            .x = p.r * c,
            .y = p.r * s,
    };
}

XYTheta RTOmega2XYTheta(const RTOmega& p) {
    float s = sin(p.v.theta);
    float c = cos(p.v.theta);
    return (XYTheta) {
            .x = p.v.r * c,
            .y = p.v.r * s,
            .theta = p.a,
    };
}

PolarVec polar_mul(const float& k, const PolarVec& p) {
    return (PolarVec) {
            .r = k * p.r,
            .theta = p.theta,
    };
}

Vec2 addv2(const Vec2& u, const Vec2& v) {
    return (Vec2) {
            .x = u.x + v.x,
            .y = u.y + v.y,
    };
}

XYTheta Vec2toXYTheta(const Vec2& v) {
    return (XYTheta) {
            .x = v.x,
            .y = v.y,
            .theta = 0,
    };
}
